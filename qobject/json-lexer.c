/*
 * JSON lexer
 *
 * Copyright IBM, Corp. 2009
 *
 * Authors:
 *  Anthony Liguori   <aliguori@us.ibm.com>
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.1 or later.
 * See the COPYING.LIB file in the top-level directory.
 *
 */

#include "qemu/osdep.h"
#include "qemu-common.h"
#include "qapi/qmp/json-lexer.h"
#include "qapi/qmp/json-streamer.h"

#define MAX_TOKEN_SIZE (64ULL << 20)

/*
 * From RFC 8259 "The JavaScript Object Notation (JSON) Data
 * Interchange Format", with [comments in brackets]:
 *
 * The set of tokens includes six structural characters, strings,
 * numbers, and three literal names.
 *
 * These are the six structural characters:
 *
 *    begin-array     = ws %x5B ws  ; [ left square bracket
 *    begin-object    = ws %x7B ws  ; { left curly bracket
 *    end-array       = ws %x5D ws  ; ] right square bracket
 *    end-object      = ws %x7D ws  ; } right curly bracket
 *    name-separator  = ws %x3A ws  ; : colon
 *    value-separator = ws %x2C ws  ; , comma
 *
 * Insignificant whitespace is allowed before or after any of the six
 * structural characters.
 * [This lexer accepts it before or after any token, which is actually
 * the same, as the grammar always has structural characters between
 * other tokens.]
 *
 *    ws = *(
 *           %x20 /              ; Space
 *           %x09 /              ; Horizontal tab
 *           %x0A /              ; Line feed or New line
 *           %x0D )              ; Carriage return
 *
 * [...] three literal names:
 *    false null true
 *  [This lexer accepts [a-z]+, and leaves rejecting unknown literal
 *  names to the parser.]
 *
 * [Numbers:]
 *
 *    number = [ minus ] int [ frac ] [ exp ]
 *    decimal-point = %x2E       ; .
 *    digit1-9 = %x31-39         ; 1-9
 *    e = %x65 / %x45            ; e E
 *    exp = e [ minus / plus ] 1*DIGIT
 *    frac = decimal-point 1*DIGIT
 *    int = zero / ( digit1-9 *DIGIT )
 *    minus = %x2D               ; -
 *    plus = %x2B                ; +
 *    zero = %x30                ; 0
 *
 * [Strings:]
 *    string = quotation-mark *char quotation-mark
 *
 *    char = unescaped /
 *        escape (
 *            %x22 /          ; "    quotation mark  U+0022
 *            %x5C /          ; \    reverse solidus U+005C
 *            %x2F /          ; /    solidus         U+002F
 *            %x62 /          ; b    backspace       U+0008
 *            %x66 /          ; f    form feed       U+000C
 *            %x6E /          ; n    line feed       U+000A
 *            %x72 /          ; r    carriage return U+000D
 *            %x74 /          ; t    tab             U+0009
 *            %x75 4HEXDIG )  ; uXXXX                U+XXXX
 *    escape = %x5C              ; \
 *    quotation-mark = %x22      ; "
 *    unescaped = %x20-21 / %x23-5B / %x5D-10FFFF
 *    [This lexer accepts any non-control character after escape, and
 *    leaves rejecting invalid ones to the parser.]
 *
 *
 * Extensions over RFC 8259:
 * - Extra escape sequence in strings:
 *   0x27 (apostrophe) is recognized after escape, too
 * - Single-quoted strings:
 *   Like double-quoted strings, except they're delimited by %x27
 *   (apostrophe) instead of %x22 (quotation mark), and can't contain
 *   unescaped apostrophe, but can contain unescaped quotation mark.
 * - Interpolation, if enabled:
 *   The lexer accepts %[A-Za-z0-9]*, and leaves rejecting invalid
 *   ones to the parser.
 *
 * Note:
 * - Input must be encoded in modified UTF-8.
 * - Decoding and validating is left to the parser.
 */

enum json_lexer_state {
    IN_ERROR = 0,               /* must really be 0, see json_lexer[] */
    IN_DQ_STRING_ESCAPE,
    IN_DQ_STRING,
    IN_SQ_STRING_ESCAPE,
    IN_SQ_STRING,
    IN_ZERO,
    IN_EXP_DIGITS,
    IN_EXP_SIGN,
    IN_EXP_E,
    IN_MANTISSA,
    IN_MANTISSA_DIGITS,
    IN_DIGITS,
    IN_SIGN,
    IN_KEYWORD,
    IN_INTERP,
    IN_WHITESPACE,
    IN_START,
    IN_START_INTERP,            /* must be IN_START + 1 */
};

QEMU_BUILD_BUG_ON((int)JSON_MIN <= (int)IN_START_INTERP);
QEMU_BUILD_BUG_ON(IN_START_INTERP != IN_START + 1);

#define TERMINAL(state) [0 ... 0x7F] = (state)

/* Return whether TERMINAL is a terminal state and the transition to it
   from OLD_STATE required lookahead.  This happens whenever the table
   below uses the TERMINAL macro.  */
#define TERMINAL_NEEDED_LOOKAHEAD(old_state, terminal) \
    (terminal != IN_ERROR && json_lexer[(old_state)][0] == (terminal))

static const uint8_t json_lexer[][256] =  {
    /* Relies on default initialization to IN_ERROR! */

    /* double quote string */
    [IN_DQ_STRING_ESCAPE] = {
        [0x20 ... 0xFD] = IN_DQ_STRING,
    },
    [IN_DQ_STRING] = {
        [0x20 ... 0xFD] = IN_DQ_STRING,
        ['\\'] = IN_DQ_STRING_ESCAPE,
        ['"'] = JSON_STRING,
    },

    /* single quote string */
    [IN_SQ_STRING_ESCAPE] = {
        [0x20 ... 0xFD] = IN_SQ_STRING,
    },
    [IN_SQ_STRING] = {
        [0x20 ... 0xFD] = IN_SQ_STRING,
        ['\\'] = IN_SQ_STRING_ESCAPE,
        ['\''] = JSON_STRING,
    },

    /* Zero */
    [IN_ZERO] = {
        TERMINAL(JSON_INTEGER),
        ['0' ... '9'] = IN_ERROR,
        ['.'] = IN_MANTISSA,
    },

    /* Float */
    [IN_EXP_DIGITS] = {
        TERMINAL(JSON_FLOAT),
        ['0' ... '9'] = IN_EXP_DIGITS,
    },

    [IN_EXP_SIGN] = {
        ['0' ... '9'] = IN_EXP_DIGITS,
    },

    [IN_EXP_E] = {
        ['-'] = IN_EXP_SIGN,
        ['+'] = IN_EXP_SIGN,
        ['0' ... '9'] = IN_EXP_DIGITS,
    },

    [IN_MANTISSA_DIGITS] = {
        TERMINAL(JSON_FLOAT),
        ['0' ... '9'] = IN_MANTISSA_DIGITS,
        ['e'] = IN_EXP_E,
        ['E'] = IN_EXP_E,
    },

    [IN_MANTISSA] = {
        ['0' ... '9'] = IN_MANTISSA_DIGITS,
    },

    /* Number */
    [IN_DIGITS] = {
        TERMINAL(JSON_INTEGER),
        ['0' ... '9'] = IN_DIGITS,
        ['e'] = IN_EXP_E,
        ['E'] = IN_EXP_E,
        ['.'] = IN_MANTISSA,
    },

    [IN_SIGN] = {
        ['0'] = IN_ZERO,
        ['1' ... '9'] = IN_DIGITS,
    },

    /* keywords */
    [IN_KEYWORD] = {
        TERMINAL(JSON_KEYWORD),
        ['a' ... 'z'] = IN_KEYWORD,
    },

    /* whitespace */
    [IN_WHITESPACE] = {
        TERMINAL(JSON_SKIP),
        [' '] = IN_WHITESPACE,
        ['\t'] = IN_WHITESPACE,
        ['\r'] = IN_WHITESPACE,
        ['\n'] = IN_WHITESPACE,
    },

    /* interpolation */
    [IN_INTERP] = {
        TERMINAL(JSON_INTERP),
        ['A' ... 'Z'] = IN_INTERP,
        ['a' ... 'z'] = IN_INTERP,
        ['0' ... '9'] = IN_INTERP,
    },

    /*
     * Two start states:
     * - IN_START recognizes JSON tokens with our string extensions
     * - IN_START_INTERP additionally recognizes interpolation.
     */
    [IN_START ... IN_START_INTERP] = {
        ['"'] = IN_DQ_STRING,
        ['\''] = IN_SQ_STRING,
        ['0'] = IN_ZERO,
        ['1' ... '9'] = IN_DIGITS,
        ['-'] = IN_SIGN,
        ['{'] = JSON_LCURLY,
        ['}'] = JSON_RCURLY,
        ['['] = JSON_LSQUARE,
        [']'] = JSON_RSQUARE,
        [','] = JSON_COMMA,
        [':'] = JSON_COLON,
        ['a' ... 'z'] = IN_KEYWORD,
        [' '] = IN_WHITESPACE,
        ['\t'] = IN_WHITESPACE,
        ['\r'] = IN_WHITESPACE,
        ['\n'] = IN_WHITESPACE,
    },
    [IN_START_INTERP]['%'] = IN_INTERP,
};

void json_lexer_init(JSONLexer *lexer, bool enable_interpolation)
{
    lexer->start_state = lexer->state = enable_interpolation
        ? IN_START_INTERP : IN_START;
    lexer->token = g_string_sized_new(3);
    lexer->x = lexer->y = 0;
}

static void json_lexer_feed_char(JSONLexer *lexer, char ch, bool flush)
{
    int char_consumed, new_state;

    lexer->x++;
    if (ch == '\n') {
        lexer->x = 0;
        lexer->y++;
    }

    do {
        assert(lexer->state <= ARRAY_SIZE(json_lexer));
        new_state = json_lexer[lexer->state][(uint8_t)ch];
        char_consumed = !TERMINAL_NEEDED_LOOKAHEAD(lexer->state, new_state);
        if (char_consumed && !flush) {
            g_string_append_c(lexer->token, ch);
        }

        switch (new_state) {
        case JSON_LCURLY:
        case JSON_RCURLY:
        case JSON_LSQUARE:
        case JSON_RSQUARE:
        case JSON_COLON:
        case JSON_COMMA:
        case JSON_INTERP:
        case JSON_INTEGER:
        case JSON_FLOAT:
        case JSON_KEYWORD:
        case JSON_STRING:
            json_message_process_token(lexer, lexer->token, new_state,
                                       lexer->x, lexer->y);
            /* fall through */
        case JSON_SKIP:
            g_string_truncate(lexer->token, 0);
            new_state = lexer->start_state;
            break;
        case IN_ERROR:
            /* XXX: To avoid having previous bad input leaving the parser in an
             * unresponsive state where we consume unpredictable amounts of
             * subsequent "good" input, percolate this error state up to the
             * parser by emitting a JSON_ERROR token, then reset lexer state.
             *
             * Also note that this handling is required for reliable channel
             * negotiation between QMP and the guest agent, since chr(0xFF)
             * is placed at the beginning of certain events to ensure proper
             * delivery when the channel is in an unknown state. chr(0xFF) is
             * never a valid ASCII/UTF-8 sequence, so this should reliably
             * induce an error/flush state.
             */
            json_message_process_token(lexer, lexer->token, JSON_ERROR,
                                       lexer->x, lexer->y);
            g_string_truncate(lexer->token, 0);
            lexer->state = lexer->start_state;
            return;
        default:
            break;
        }
        lexer->state = new_state;
    } while (!char_consumed && !flush);

    /* Do not let a single token grow to an arbitrarily large size,
     * this is a security consideration.
     */
    if (lexer->token->len > MAX_TOKEN_SIZE) {
        json_message_process_token(lexer, lexer->token, lexer->state,
                                   lexer->x, lexer->y);
        g_string_truncate(lexer->token, 0);
        lexer->state = lexer->start_state;
    }
}

void json_lexer_feed(JSONLexer *lexer, const char *buffer, size_t size)
{
    size_t i;

    for (i = 0; i < size; i++) {
        json_lexer_feed_char(lexer, buffer[i], false);
    }
}

void json_lexer_flush(JSONLexer *lexer)
{
    if (lexer->state != lexer->start_state) {
        json_lexer_feed_char(lexer, 0, true);
    }
    json_message_process_token(lexer, lexer->token, JSON_END_OF_INPUT,
                               lexer->x, lexer->y);
}

void json_lexer_destroy(JSONLexer *lexer)
{
    g_string_free(lexer->token, true);
}
