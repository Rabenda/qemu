/* RISC-V ISA constants */

#ifndef TARGET_RISCV_CPU_BITS_H
#define TARGET_RISCV_CPU_BITS_H

#define get_field(reg, mask) (((reg) & \
                 (uint64_t)(mask)) / ((mask) & ~((mask) << 1)))
#define set_field(reg, mask, val) (((reg) & ~(uint64_t)(mask)) | \
                 (((uint64_t)(val) * ((mask) & ~((mask) << 1))) & \
                 (uint64_t)(mask)))

/* Floating point round mode */
#define FSR_RD_SHIFT        5
#define FSR_RD              (0x7 << FSR_RD_SHIFT)

/* Floating point accrued exception flags */
#define FPEXC_NX            0x01
#define FPEXC_UF            0x02
#define FPEXC_OF            0x04
#define FPEXC_DZ            0x08
#define FPEXC_NV            0x10

/* Floating point status register bits */
#define FSR_AEXC_SHIFT      0
#define FSR_NVA             (FPEXC_NV << FSR_AEXC_SHIFT)
#define FSR_OFA             (FPEXC_OF << FSR_AEXC_SHIFT)
#define FSR_UFA             (FPEXC_UF << FSR_AEXC_SHIFT)
#define FSR_DZA             (FPEXC_DZ << FSR_AEXC_SHIFT)
#define FSR_NXA             (FPEXC_NX << FSR_AEXC_SHIFT)
#define FSR_AEXC            (FSR_NVA | FSR_OFA | FSR_UFA | FSR_DZA | FSR_NXA)

/* Floating point round mode in fxcr */
#define FXCR_RD_SHIFT       24
#define FXCR_RD             (0x7 << FXCR_RD_SHIFT)

/* Vector Fixed-Point round model */
#define FSR_VXRM_SHIFT      9
#define FSR_VXRM            (0x3 << FSR_VXRM_SHIFT)

/* Vector Fixed-Point saturation flag */
#define FSR_VXSAT_SHIFT     8
#define FSR_VXSAT           (0x1 << FSR_VXSAT_SHIFT)

/* Control and Status Registers */

/* User Trap Setup */
#define CSR_USTATUS         0x000
#define CSR_UIE             0x004
#define CSR_UTVEC           0x005

/* User Trap Handling */
#define CSR_USCRATCH        0x040
#define CSR_UEPC            0x041
#define CSR_UCAUSE          0x042
#define CSR_UTVAL           0x043
#define CSR_UIP             0x044

/* User Floating-Point CSRs */
#define CSR_FFLAGS          0x001
#define CSR_FRM             0x002
#define CSR_FCSR            0x003

/* User Vector CSRs */
#define CSR_VSTART          0x008
#define CSR_VXSAT           0x009
#define CSR_VXRM            0x00a
#define CSR_VL              0xc20
#define CSR_VTYPE           0xc21

/* User Timers and Counters */
#define CSR_CYCLE           0xc00
#define CSR_TIME            0xc01
#define CSR_INSTRET         0xc02
#define CSR_HPMCOUNTER3     0xc03
#define CSR_HPMCOUNTER4     0xc04
#define CSR_HPMCOUNTER5     0xc05
#define CSR_HPMCOUNTER6     0xc06
#define CSR_HPMCOUNTER7     0xc07
#define CSR_HPMCOUNTER8     0xc08
#define CSR_HPMCOUNTER9     0xc09
#define CSR_HPMCOUNTER10    0xc0a
#define CSR_HPMCOUNTER11    0xc0b
#define CSR_HPMCOUNTER12    0xc0c
#define CSR_HPMCOUNTER13    0xc0d
#define CSR_HPMCOUNTER14    0xc0e
#define CSR_HPMCOUNTER15    0xc0f
#define CSR_HPMCOUNTER16    0xc10
#define CSR_HPMCOUNTER17    0xc11
#define CSR_HPMCOUNTER18    0xc12
#define CSR_HPMCOUNTER19    0xc13
#define CSR_HPMCOUNTER20    0xc14
#define CSR_HPMCOUNTER21    0xc15
#define CSR_HPMCOUNTER22    0xc16
#define CSR_HPMCOUNTER23    0xc17
#define CSR_HPMCOUNTER24    0xc18
#define CSR_HPMCOUNTER25    0xc19
#define CSR_HPMCOUNTER26    0xc1a
#define CSR_HPMCOUNTER27    0xc1b
#define CSR_HPMCOUNTER28    0xc1c
#define CSR_HPMCOUNTER29    0xc1d
#define CSR_HPMCOUNTER30    0xc1e
#define CSR_HPMCOUNTER31    0xc1f
#define CSR_CYCLEH          0xc80
#define CSR_TIMEH           0xc81
#define CSR_INSTRETH        0xc82
#define CSR_HPMCOUNTER3H    0xc83
#define CSR_HPMCOUNTER4H    0xc84
#define CSR_HPMCOUNTER5H    0xc85
#define CSR_HPMCOUNTER6H    0xc86
#define CSR_HPMCOUNTER7H    0xc87
#define CSR_HPMCOUNTER8H    0xc88
#define CSR_HPMCOUNTER9H    0xc89
#define CSR_HPMCOUNTER10H   0xc8a
#define CSR_HPMCOUNTER11H   0xc8b
#define CSR_HPMCOUNTER12H   0xc8c
#define CSR_HPMCOUNTER13H   0xc8d
#define CSR_HPMCOUNTER14H   0xc8e
#define CSR_HPMCOUNTER15H   0xc8f
#define CSR_HPMCOUNTER16H   0xc90
#define CSR_HPMCOUNTER17H   0xc91
#define CSR_HPMCOUNTER18H   0xc92
#define CSR_HPMCOUNTER19H   0xc93
#define CSR_HPMCOUNTER20H   0xc94
#define CSR_HPMCOUNTER21H   0xc95
#define CSR_HPMCOUNTER22H   0xc96
#define CSR_HPMCOUNTER23H   0xc97
#define CSR_HPMCOUNTER24H   0xc98
#define CSR_HPMCOUNTER25H   0xc99
#define CSR_HPMCOUNTER26H   0xc9a
#define CSR_HPMCOUNTER27H   0xc9b
#define CSR_HPMCOUNTER28H   0xc9c
#define CSR_HPMCOUNTER29H   0xc9d
#define CSR_HPMCOUNTER30H   0xc9e
#define CSR_HPMCOUNTER31H   0xc9f

/* Machine Timers and Counters */
#define CSR_MCYCLE          0xb00
#define CSR_MINSTRET        0xb02
#define CSR_MCYCLEH         0xb80
#define CSR_MINSTRETH       0xb82

/* Machine Information Registers */
#define CSR_MVENDORID       0xf11
#define CSR_MARCHID         0xf12
#define CSR_MIMPID          0xf13
#define CSR_MHARTID         0xf14

/* Machine Trap Setup */
#define CSR_MSTATUS         0x300
#define CSR_MISA            0x301
#define CSR_MEDELEG         0x302
#define CSR_MIDELEG         0x303
#define CSR_MIE             0x304
#define CSR_MTVEC           0x305
#define CSR_MCOUNTEREN      0x306
#define CSR_MTVT            0x307 /* clic-spec-draft */

/* 32-bit only */
#define CSR_MSTATUSH        0x310

/* Machine Trap Handling */
#define CSR_MSCRATCH        0x340
#define CSR_MEPC            0x341
#define CSR_MCAUSE          0x342
#define CSR_MTVAL           0x343
#define CSR_MIP             0x344
#define CSR_MNXTI           0x345 /* clic-spec-draft */
#define CSR_MINTSTATUS      0x346 /* clic-spec-draft */
#define CSR_MINTTHRESH      0x347 /* clic-spec-draft */

/* Supervisor Trap Setup */
#define CSR_SSTATUS         0x100
#define CSR_SEDELEG         0x102
#define CSR_SIDELEG         0x103
#define CSR_SIE             0x104
#define CSR_STVEC           0x105
#define CSR_SCOUNTEREN      0x106
#define CSR_STVT            0x107 /* clic-spec-draft */

/* Supervisor Trap Handling */
#define CSR_SSCRATCH        0x140
#define CSR_SEPC            0x141
#define CSR_SCAUSE          0x142
#define CSR_STVAL           0x143
#define CSR_SIP             0x144
#define CSR_SNXTI           0x145 /* clic-spec-draft */
#define CSR_SINTSTATUS      0x146 /* clic-spec-draft */
#define CSR_SINTTHRESH      0x147 /* clic-spec-draft */

/* Supervisor Protection and Translation */
#define CSR_SPTBR           0x180
#define CSR_SATP            0x180

/* Hpervisor CSRs */
#define CSR_HSTATUS         0x600
#define CSR_HEDELEG         0x602
#define CSR_HIDELEG         0x603
#define CSR_HIE             0x604
#define CSR_HCOUNTEREN      0x606
#define CSR_HGEIE           0x607
#define CSR_HTVAL           0x643
#define CSR_HVIP            0x645
#define CSR_HIP             0x644
#define CSR_HTINST          0x64A
#define CSR_HGEIP           0xE12
#define CSR_HGATP           0x680
#define CSR_HTIMEDELTA      0x605
#define CSR_HTIMEDELTAH     0x615

/* Virtual CSRs */
#define CSR_VSSTATUS        0x200
#define CSR_VSIE            0x204
#define CSR_VSTVEC          0x205
#define CSR_VSSCRATCH       0x240
#define CSR_VSEPC           0x241
#define CSR_VSCAUSE         0x242
#define CSR_VSTVAL          0x243
#define CSR_VSIP            0x244
#define CSR_VSATP           0x280

#define CSR_MTINST          0x34a
#define CSR_MTVAL2          0x34b

/* Enhanced Physical Memory Protection (ePMP) */
#define CSR_MSECCFG         0x390
#define CSR_MSECCFGH        0x391
/* Physical Memory Protection */
#define CSR_PMPCFG0         0x3a0
#define CSR_PMPCFG1         0x3a1
#define CSR_PMPCFG2         0x3a2
#define CSR_PMPCFG3         0x3a3
#define CSR_PMPADDR0        0x3b0
#define CSR_PMPADDR1        0x3b1
#define CSR_PMPADDR2        0x3b2
#define CSR_PMPADDR3        0x3b3
#define CSR_PMPADDR4        0x3b4
#define CSR_PMPADDR5        0x3b5
#define CSR_PMPADDR6        0x3b6
#define CSR_PMPADDR7        0x3b7
#define CSR_PMPADDR8        0x3b8
#define CSR_PMPADDR9        0x3b9
#define CSR_PMPADDR10       0x3ba
#define CSR_PMPADDR11       0x3bb
#define CSR_PMPADDR12       0x3bc
#define CSR_PMPADDR13       0x3bd
#define CSR_PMPADDR14       0x3be
#define CSR_PMPADDR15       0x3bf

/* Debug/Trace Registers (shared with Debug Mode) */
#define CSR_TSELECT         0x7a0
#define CSR_TDATA1          0x7a1
#define CSR_TDATA2          0x7a2
#define CSR_TDATA3          0x7a3

/* Debug Mode Registers */
#define CSR_DCSR            0x7b0
#define CSR_DPC             0x7b1
#define CSR_DSCRATCH        0x7b2

/* X-Thead Extend registers */
#define CSR_MXSTATUS        0x7c0
#define CSR_MHCR            0x7c1
#define CSR_MCOR            0x7c2
#define CSR_MCCR2           0x7c3
#define CSR_MCER2           0x7c4
#define CSR_MHINT           0x7c5
#define CSR_MRMR            0x7c6
#define CSR_MRVBR           0x7c7
#define CSR_MCER            0x7c8
#define CSR_MCOUNTERWEN     0x7c9
#define CSR_MCOUNTERINTEN   0x7ca
#define CSR_MCOUNTEROF      0x7cb
#define CSR_MHINT2          0x7cc

#define CSR_USP             0x7d1
#define CSR_MCINS           0x7d2
#define CSR_MCINDEX         0x7d3
#define CSR_MCDATA0         0x7d4
#define CSR_MCDATA1         0x7d5
#define CSR_MEICR           0x7d6
#define CSR_MEICR2          0x7d7

#define CSR_MRADDR          0x7e0
#define CSR_MEXSTATUS       0x7e1
#define CSR_MNMICAUSE       0x7e2
#define CSR_MNMIPC          0x7e3

#define CSR_CPUID           0xfc0

#define CSR_SXSTATUS        0x5c0
#define CSR_SHCR            0x5c1
#define CSR_SCER2           0x5c2
#define CSR_SCER            0x5c3
#define CSR_SCOUNTERINTEN   0x5c4
#define CSR_SCOUNTEROF      0x5c5
#define CSR_CYCLE_C910      0x5e0
#define CSR_SHPMCOUNTER1    0x5e1
#define CSR_SHPMCOUNTER2    0x5e2
#define CSR_SHPMCOUNTER3    0x5e3
#define CSR_SHPMCOUNTER4    0x5e4
#define CSR_SHPMCOUNTER5    0x5e5
#define CSR_SHPMCOUNTER6    0x5e6
#define CSR_SHPMCOUNTER7    0x5e7
#define CSR_SHPMCOUNTER8    0x5e8
#define CSR_SHPMCOUNTER9    0x5e9
#define CSR_SHPMCOUNTER10   0x5ea
#define CSR_SHPMCOUNTER11   0x5eb
#define CSR_SHPMCOUNTER12   0x5ec
#define CSR_SHPMCOUNTER13   0x5ed
#define CSR_SHPMCOUNTER14   0x5ee
#define CSR_SHPMCOUNTER15   0x5ef
#define CSR_SHPMCOUNTER16   0x5f0
#define CSR_SHPMCOUNTER17   0x5f1
#define CSR_SHPMCOUNTER18   0x5f2
#define CSR_SHPMCOUNTER19   0x5f3
#define CSR_SHPMCOUNTER20   0x5f4
#define CSR_SHPMCOUNTER21   0x5f5
#define CSR_SHPMCOUNTER22   0x5f6
#define CSR_SHPMCOUNTER23   0x5f7
#define CSR_SHPMCOUNTER24   0x5f8
#define CSR_SHPMCOUNTER25   0x5f9
#define CSR_SHPMCOUNTER26   0x5fa
#define CSR_SHPMCOUNTER27   0x5fb
#define CSR_SHPMCOUNTER28   0x5fc
#define CSR_SHPMCOUNTER29   0x5fd
#define CSR_SHPMCOUNTER30   0x5fe
#define CSR_SHPMCOUNTER31   0x5ff

#define CSR_SMIR            0x9c0
#define CSR_SMLO0           0x9c1
#define CSR_SMEH            0x9c2
#define CSR_SMCIR           0x9c3

#define CSR_FXCR            0x800

#define MEXSTATUS_EXPT      0x20
#define MEXSTATUS_SPSWAP    0x20000

/* Performance Counters */
#define CSR_MHPMCOUNTER3    0xb03
#define CSR_MHPMCOUNTER4    0xb04
#define CSR_MHPMCOUNTER5    0xb05
#define CSR_MHPMCOUNTER6    0xb06
#define CSR_MHPMCOUNTER7    0xb07
#define CSR_MHPMCOUNTER8    0xb08
#define CSR_MHPMCOUNTER9    0xb09
#define CSR_MHPMCOUNTER10   0xb0a
#define CSR_MHPMCOUNTER11   0xb0b
#define CSR_MHPMCOUNTER12   0xb0c
#define CSR_MHPMCOUNTER13   0xb0d
#define CSR_MHPMCOUNTER14   0xb0e
#define CSR_MHPMCOUNTER15   0xb0f
#define CSR_MHPMCOUNTER16   0xb10
#define CSR_MHPMCOUNTER17   0xb11
#define CSR_MHPMCOUNTER18   0xb12
#define CSR_MHPMCOUNTER19   0xb13
#define CSR_MHPMCOUNTER20   0xb14
#define CSR_MHPMCOUNTER21   0xb15
#define CSR_MHPMCOUNTER22   0xb16
#define CSR_MHPMCOUNTER23   0xb17
#define CSR_MHPMCOUNTER24   0xb18
#define CSR_MHPMCOUNTER25   0xb19
#define CSR_MHPMCOUNTER26   0xb1a
#define CSR_MHPMCOUNTER27   0xb1b
#define CSR_MHPMCOUNTER28   0xb1c
#define CSR_MHPMCOUNTER29   0xb1d
#define CSR_MHPMCOUNTER30   0xb1e
#define CSR_MHPMCOUNTER31   0xb1f
#define CSR_MHPMEVENT3      0x323
#define CSR_MHPMEVENT4      0x324
#define CSR_MHPMEVENT5      0x325
#define CSR_MHPMEVENT6      0x326
#define CSR_MHPMEVENT7      0x327
#define CSR_MHPMEVENT8      0x328
#define CSR_MHPMEVENT9      0x329
#define CSR_MHPMEVENT10     0x32a
#define CSR_MHPMEVENT11     0x32b
#define CSR_MHPMEVENT12     0x32c
#define CSR_MHPMEVENT13     0x32d
#define CSR_MHPMEVENT14     0x32e
#define CSR_MHPMEVENT15     0x32f
#define CSR_MHPMEVENT16     0x330
#define CSR_MHPMEVENT17     0x331
#define CSR_MHPMEVENT18     0x332
#define CSR_MHPMEVENT19     0x333
#define CSR_MHPMEVENT20     0x334
#define CSR_MHPMEVENT21     0x335
#define CSR_MHPMEVENT22     0x336
#define CSR_MHPMEVENT23     0x337
#define CSR_MHPMEVENT24     0x338
#define CSR_MHPMEVENT25     0x339
#define CSR_MHPMEVENT26     0x33a
#define CSR_MHPMEVENT27     0x33b
#define CSR_MHPMEVENT28     0x33c
#define CSR_MHPMEVENT29     0x33d
#define CSR_MHPMEVENT30     0x33e
#define CSR_MHPMEVENT31     0x33f
#define CSR_MHPMCOUNTER3H   0xb83
#define CSR_MHPMCOUNTER4H   0xb84
#define CSR_MHPMCOUNTER5H   0xb85
#define CSR_MHPMCOUNTER6H   0xb86
#define CSR_MHPMCOUNTER7H   0xb87
#define CSR_MHPMCOUNTER8H   0xb88
#define CSR_MHPMCOUNTER9H   0xb89
#define CSR_MHPMCOUNTER10H  0xb8a
#define CSR_MHPMCOUNTER11H  0xb8b
#define CSR_MHPMCOUNTER12H  0xb8c
#define CSR_MHPMCOUNTER13H  0xb8d
#define CSR_MHPMCOUNTER14H  0xb8e
#define CSR_MHPMCOUNTER15H  0xb8f
#define CSR_MHPMCOUNTER16H  0xb90
#define CSR_MHPMCOUNTER17H  0xb91
#define CSR_MHPMCOUNTER18H  0xb92
#define CSR_MHPMCOUNTER19H  0xb93
#define CSR_MHPMCOUNTER20H  0xb94
#define CSR_MHPMCOUNTER21H  0xb95
#define CSR_MHPMCOUNTER22H  0xb96
#define CSR_MHPMCOUNTER23H  0xb97
#define CSR_MHPMCOUNTER24H  0xb98
#define CSR_MHPMCOUNTER25H  0xb99
#define CSR_MHPMCOUNTER26H  0xb9a
#define CSR_MHPMCOUNTER27H  0xb9b
#define CSR_MHPMCOUNTER28H  0xb9c
#define CSR_MHPMCOUNTER29H  0xb9d
#define CSR_MHPMCOUNTER30H  0xb9e
#define CSR_MHPMCOUNTER31H  0xb9f

/* mstatus CSR bits */
#define MSTATUS_UIE         0x00000001
#define MSTATUS_SIE         0x00000002
#define MSTATUS_MIE         0x00000008
#define MSTATUS_UPIE        0x00000010
#define MSTATUS_SPIE        0x00000020
#define MSTATUS_UBE         0x00000040
#define MSTATUS_MPIE        0x00000080
#define MSTATUS_SPP         0x00000100
#define MSTATUS_MPP         0x00001800
#define MSTATUS_FS          0x00006000
#define MSTATUS_XS          0x00018000
#define MSTATUS_MPRV        0x00020000
#define MSTATUS_SUM         0x00040000 /* since: priv-1.10 */
#define MSTATUS_MXR         0x00080000
#define MSTATUS_TVM         0x00100000 /* since: priv-1.10 */
#define MSTATUS_TW          0x00200000 /* since: priv-1.10 */
#define MSTATUS_TSR         0x00400000 /* since: priv-1.10 */
#define MSTATUS_GVA         0x4000000000ULL
#define MSTATUS_MPV         0x8000000000ULL

#define MSTATUS64_UXL       0x0000000300000000ULL
#define MSTATUS64_SXL       0x0000000C00000000ULL

#define MSTATUS32_SD        0x80000000
#define MSTATUS64_SD        0x8000000000000000ULL

#define MISA32_MXL          0xC0000000
#define MISA64_MXL          0xC000000000000000ULL

#define MXL_RV32            1
#define MXL_RV64            2
#define MXL_RV128           3

/* sstatus CSR bits */
#define SSTATUS_UIE         0x00000001
#define SSTATUS_SIE         0x00000002
#define SSTATUS_UPIE        0x00000010
#define SSTATUS_SPIE        0x00000020
#define SSTATUS_SPP         0x00000100
#define SSTATUS_FS          0x00006000
#define SSTATUS_XS          0x00018000
#define SSTATUS_SUM         0x00040000 /* since: priv-1.10 */
#define SSTATUS_MXR         0x00080000

#define SSTATUS32_SD        0x80000000
#define SSTATUS64_SD        0x8000000000000000ULL

/* hstatus CSR bits */
#define HSTATUS_VSBE         0x00000020
#define HSTATUS_GVA          0x00000040
#define HSTATUS_SPV          0x00000080
#define HSTATUS_SPVP         0x00000100
#define HSTATUS_HU           0x00000200
#define HSTATUS_VGEIN        0x0003F000
#define HSTATUS_VTVM         0x00100000
#define HSTATUS_VTW          0x00200000
#define HSTATUS_VTSR         0x00400000
#define HSTATUS_VSXL         0x300000000

#define HSTATUS32_WPRI       0xFF8FF87E
#define HSTATUS64_WPRI       0xFFFFFFFFFF8FF87EULL

#define HCOUNTEREN_CY        (1 << 0)
#define HCOUNTEREN_TM        (1 << 1)
#define HCOUNTEREN_IR        (1 << 2)
#define HCOUNTEREN_HPM3      (1 << 3)

/* Privilege modes */
#define PRV_U 0
#define PRV_S 1
#define PRV_H 2 /* Reserved */
#define PRV_M 3

/* Virtulisation Register Fields */
#define VIRT_ONOFF          1
/* This is used to save state for when we take an exception. If this is set
 * that means that we want to force a HS level exception (no matter what the
 * delegation is set to). This will occur for things such as a second level
 * page table fault.
 */
#define FORCE_HS_EXCEP      2

/* RV32 satp CSR field masks */
#define SATP32_MODE         0x80000000
#define SATP32_ASID         0x7fc00000
#define SATP32_PPN          0x003fffff

/* RV64 satp CSR field masks */
#define SATP64_MODE         0xF000000000000000ULL
#define SATP64_ASID         0x0FFFF00000000000ULL
#define SATP64_PPN          0x00000FFFFFFFFFFFULL

/* VM modes (mstatus.vm) privileged ISA 1.9.1 */
#define VM_1_09_MBARE       0
#define VM_1_09_MBB         1
#define VM_1_09_MBBID       2
#define VM_1_09_SV32        8
#define VM_1_09_SV39        9
#define VM_1_09_SV48        10

/* VM modes (satp.mode) privileged ISA 1.10 */
#define VM_1_10_MBARE       0
#define VM_1_10_SV32        1
#define VM_1_10_SV39        8
#define VM_1_10_SV48        9
#define VM_1_10_SV57        10
#define VM_1_10_SV64        11

/* Page table entry (PTE) fields */
#define PTE_V               0x001 /* Valid */
#define PTE_R               0x002 /* Read */
#define PTE_W               0x004 /* Write */
#define PTE_X               0x008 /* Execute */
#define PTE_U               0x010 /* User */
#define PTE_G               0x020 /* Global */
#define PTE_A               0x040 /* Accessed */
#define PTE_D               0x080 /* Dirty */
#define PTE_SOFT            0x300 /* Reserved for Software */

/* Page table PPN shift amount */
#define PTE_PPN_SHIFT       10

/* Leaf page shift amount */
#define PGSHIFT             12

/* Default Reset Vector adress */
#define DEFAULT_RSTVEC      0x1000

/* Exception causes */
typedef enum RISCVException {
    RISCV_EXCP_NONE = -1, /* sentinel value */
    RISCV_EXCP_INST_ADDR_MIS = 0x0,
    RISCV_EXCP_INST_ACCESS_FAULT = 0x1,
    RISCV_EXCP_ILLEGAL_INST = 0x2,
    RISCV_EXCP_BREAKPOINT = 0x3,
    RISCV_EXCP_LOAD_ADDR_MIS = 0x4,
    RISCV_EXCP_LOAD_ACCESS_FAULT = 0x5,
    RISCV_EXCP_STORE_AMO_ADDR_MIS = 0x6,
    RISCV_EXCP_STORE_AMO_ACCESS_FAULT = 0x7,
    RISCV_EXCP_U_ECALL = 0x8,
    RISCV_EXCP_S_ECALL = 0x9,
    RISCV_EXCP_VS_ECALL = 0xa,
    RISCV_EXCP_M_ECALL = 0xb,
    RISCV_EXCP_INST_PAGE_FAULT = 0xc, /* since: priv-1.10.0 */
    RISCV_EXCP_LOAD_PAGE_FAULT = 0xd, /* since: priv-1.10.0 */
    RISCV_EXCP_STORE_PAGE_FAULT = 0xf, /* since: priv-1.10.0 */
    RISCV_EXCP_SEMIHOST = 0x10,
    RISCV_EXCP_INST_GUEST_PAGE_FAULT = 0x14,
    RISCV_EXCP_LOAD_GUEST_ACCESS_FAULT = 0x15,
    RISCV_EXCP_VIRT_INSTRUCTION_FAULT = 0x16,
    RISCV_EXCP_STORE_GUEST_AMO_ACCESS_FAULT = 0x17,
} RISCVException;

#define RISCV_EXCP_INT_CLIC                0x40000000
#define RISCV_EXCP_INT_FLAG                0x80000000
#define RISCV_EXCP_INT_MASK                0x7fffffff

/* Interrupt causes */
#define IRQ_U_SOFT                         0
#define IRQ_S_SOFT                         1
#define IRQ_VS_SOFT                        2
#define IRQ_M_SOFT                         3
#define IRQ_U_TIMER                        4
#define IRQ_S_TIMER                        5
#define IRQ_VS_TIMER                       6
#define IRQ_M_TIMER                        7
#define IRQ_U_EXT                          8
#define IRQ_S_EXT                          9
#define IRQ_VS_EXT                         10
#define IRQ_M_EXT                          11

/* mip masks */
#define MIP_USIP                           (1 << IRQ_U_SOFT)
#define MIP_SSIP                           (1 << IRQ_S_SOFT)
#define MIP_VSSIP                          (1 << IRQ_VS_SOFT)
#define MIP_MSIP                           (1 << IRQ_M_SOFT)
#define MIP_UTIP                           (1 << IRQ_U_TIMER)
#define MIP_STIP                           (1 << IRQ_S_TIMER)
#define MIP_VSTIP                          (1 << IRQ_VS_TIMER)
#define MIP_MTIP                           (1 << IRQ_M_TIMER)
#define MIP_UEIP                           (1 << IRQ_U_EXT)
#define MIP_SEIP                           (1 << IRQ_S_EXT)
#define MIP_VSEIP                          (1 << IRQ_VS_EXT)
#define MIP_MEIP                           (1 << IRQ_M_EXT)

/* sip masks */
#define SIP_SSIP                           MIP_SSIP
#define SIP_STIP                           MIP_STIP
#define SIP_SEIP                           MIP_SEIP

/* mintstatus */
#define MINTSTATUS_MIL                     0xff000000 /* mil[7:0] */
#define MINTSTATUS_SIL                     0x0000ff00 /* sil[7:0] */
#define MINTSTATUS_UIL                     0x000000ff /* uil[7:0] */

/* mcause */
#define MCAUSE_MINHV                       0x40000000 /* minhv */
#define MCAUSE_MPP                         0x30000000 /* mpp[1:0] */
#define MCAUSE_MPIE                        0x08000000 /* mpie */
#define MCAUSE_MPIL                        0x00ff0000 /* mpil[7:0] */
#define MCAUSE_EXCCODE                     0x00000fff /* exccode[11:0] */

/* sintstatus */
#define SINTSTATUS_SIL                     0x0000ff00 /* sil[7:0] */
#define SINTSTATUS_UIL                     0x000000ff /* uil[7:0] */

/* scause */
#define SCAUSE_SINHV                       0x40000000 /* sinhv */
#define SCAUSE_SPP                         0x10000000 /* spp */
#define SCAUSE_SPIE                        0x08000000 /* spie */
#define SCAUSE_SPIL                        0x00ff0000 /* spil[7:0] */
#define SCAUSE_EXCCODE                     0x00000fff /* exccode[11:0] */

/* MIE masks */
#define MIE_SEIE                           (1 << IRQ_S_EXT)
#define MIE_UEIE                           (1 << IRQ_U_EXT)
#define MIE_STIE                           (1 << IRQ_S_TIMER)
#define MIE_UTIE                           (1 << IRQ_U_TIMER)
#define MIE_SSIE                           (1 << IRQ_S_SOFT)
#define MIE_USIE                           (1 << IRQ_U_SOFT)
#endif
