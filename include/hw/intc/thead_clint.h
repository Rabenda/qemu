/*
 * T-HEAD CLINT (Core Local Interruptor) header.
 *
 * Copyright (c) 2021 T-Head Semiconductor Co., Ltd. All rights reserved.
 *
 * This provides real-time clock, timer and interprocessor interrupts.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2 or later, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef THEAD_CLINT_H
#define THEAD_CLINT_H

#include "hw/irq.h"
#include "qemu/timer.h"

#define TYPE_THEAD_CLINT "thead_clint"
#define THEAD_CLINT(obj) \
    OBJECT_CHECK(THEADCLINTState, (obj), TYPE_THEAD_CLINT)

typedef struct THEADCLINTCState {
    /*< private >*/
    SysBusDevice parent_obj;

    uint32_t msip;
    uint64_t mtimecmp;
    QEMUTimer *timer;
    MemoryRegion mmio;
    qemu_irq irq[2];
} THEADCLINTState;
DeviceState *thead_clint_create(hwaddr addr, qemu_irq msip,
                                qemu_irq mtip);
#endif
