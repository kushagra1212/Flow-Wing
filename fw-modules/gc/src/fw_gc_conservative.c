/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "fw_gc.h"
#include "fw_gc_internal.h"
#include <setjmp.h>
#include <stdint.h>

/* High end of the C call stack, recorded by fw_gc_set_stack_base (typically
   the address of a local in main). NULL disables conservative scanning. */
void *g_stack_base = NULL;

void fw_gc_set_stack_base(void *stack_base) {
  g_stack_base = stack_base;
}

/* If `p` points anywhere inside a live object's payload (interior pointers
   included), return that object's payload base; otherwise NULL. */
static void *fw_gc_object_containing(void *p) {
  uintptr_t q = (uintptr_t)p;
  for (FWObjHeader *h = g_all_objects; h != NULL; h = h->next) {
    uintptr_t lo = (uintptr_t)fw_payload(h);
    uintptr_t hi = lo + h->size;                 /* one past the last byte */
    if (q >= lo && q < hi) return (void *)lo;
  }
  return NULL;
}

/* Conservatively scan the C stack: treat every aligned machine word between
   the current frame and g_stack_base as a potential root. Any word that
   resolves to a live object (via an interior or exact pointer) is seeded onto
   the mark work-list. */
void fw_gc_scan_stack_conservative(void) {
  if (!g_stack_base) return;

  /* Spill callee-saved registers to the stack so pointers held only in
     registers become visible to the word-by-word walk below. Using setjmp as
     the controlling expression of `if` is the one form the C standard blesses
     (assigning its result is undefined) and it also consumes the return value,
     which keeps the register spill observable. The taken branch is never
     reached — nothing calls longjmp on `regs`. */
  jmp_buf regs;
  if (setjmp(regs) != 0) return;

  /* Address of a local marks the current (low, most-recently-pushed) end. */
  volatile int anchor;
  uintptr_t here = (uintptr_t)&anchor;
  uintptr_t base = (uintptr_t)g_stack_base;

  /* Normalize so lo <= hi regardless of stack growth direction. */
  uintptr_t lo = here < base ? here : base;
  uintptr_t hi = here < base ? base : here;

  /* Round the low end up to a pointer-size boundary. The compiler stores
     8-byte pointers on 8-aligned slots, so an unaligned `lo` would put the
     word-stride lattice permanently off those slots and miss every root. */
  const uintptr_t align = sizeof(void *);
  lo = (lo + (align - 1)) & ~(align - 1);

  /* Walk aligned words; only read a full word that fits within [lo, hi). */
  for (uintptr_t a = lo; a + sizeof(void *) <= hi; a += sizeof(void *)) {
    void *word = *(void **)a;
    void *obj = fw_gc_object_containing(word);
    if (obj) fw_gc_push_root_object(obj);
  }
}
