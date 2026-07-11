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


#pragma once
#include "fw_gc.h"
#include <stddef.h>

#define FW_MARK_BIT  ((uintptr_t)1)
#define FW_PIN_BIT   ((uintptr_t)2)
#define FW_FLAG_MASK ((uintptr_t)0x7)

/* Per-object header. Program pointer points just past this. */
typedef struct FWObjHeader {
  struct FWObjHeader *next;            /* threads ALL live objects (for sweep) */
  uintptr_t           desc_and_flags;  /* descriptor pointer | pin | mark */
  size_t              size;            /* payload bytes (excludes header) */
} FWObjHeader;

#define FW_HEADER_SIZE (sizeof(FWObjHeader))

static inline void *fw_payload(FWObjHeader *h) {
  return (void *)((char *)h + FW_HEADER_SIZE);
}
static inline FWObjHeader *fw_header(void *payload) {
  return (FWObjHeader *)((char *)payload - FW_HEADER_SIZE);
}

/* Shared globals (defined in fw_gc_core.c). */
extern FWObjHeader *g_all_objects;   /* head of the all-objects list */
extern FWGCStats    g_stats;
extern int          g_stress;
extern size_t       g_threshold;     /* live_bytes level that triggers a collect */

/* Global roots: a simple growable array of void** slots. */
extern void  **g_global_roots;
extern size_t  g_global_roots_len;
extern size_t  g_global_roots_cap;

typedef struct FWFinalizer {
  void  *obj;
  void (*fn)(void *);
  struct FWFinalizer *next;
} FWFinalizer;
extern FWFinalizer *g_finalizers;

/* Conservative stack scanning (defined in fw_gc_conservative.c). */
extern void *g_stack_base;                    /* high end of the C stack */
void fw_gc_scan_stack_conservative(void);

/* Push a non-NULL heap object onto the mark work-list (defined in
   fw_gc_mark.c). Shared by the root-seeding paths and the conservative
   scanner. */
void fw_gc_push_root_object(void *obj);
