/*
 * pongoOS - https://checkra.in
 *
 * Copyright (C) 2019-2023 checkra1n team
 *
 * This file is part of pongoOS.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#include "fuse/fuse_private.h"
#include "dt/dt_private.h"
#include "recfg/recfg_soc.h"
#include "pongo.h"
#include <reent.h>

boot_args *gBootArgs;
uint64_t gTopOfKernelData;
void *gEntryPoint;
volatile char gBootFlag = 0;
uint64_t gIOBase;

char* gDevType;
uint64_t gESTS;

struct task sched_task = {.name = "sched"};
struct task pongo_task = {.name = "main"};

struct task* pongo_sched_head;

char soc_name[9] = {};
uint32_t socnum = 0x0;
void (*sep_boot_hook)(void);

uint32_t preempt_ctr;

int pongo_fiq_handler(void) { return -1; }

extern void pongo_main_task(uint64_t*);

_Noreturn void pongo_entry(uint64_t *kernel_args, void *entryp, void (*exit_to_el1_image)(void *boot_args, void *boot_entry_point, void *trampoline))
{
    pongo_main_task(kernel_args, entryp);
    while (1);
}
