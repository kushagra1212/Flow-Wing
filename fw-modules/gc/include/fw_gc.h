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
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Descriptor kinds — how to find pointers inside an object. */
typedef enum {
  FW_KIND_PLAIN = 0,  /* fixed pointer offsets (classes) */
  FW_KIND_BLOB  = 1,  /* no interior pointers (string buffers) */
  FW_KIND_TAGGED= 2,  /* pointer-ness depends on a runtime tag (dynamic) */
  FW_KIND_ARRAY = 3   /* repeat an element descriptor N times (containers) */
} FWKind;

/* Custom trace callback: for objects whose live GC pointers live in memory the
   static layout fields cannot describe — e.g. an FFI container that keeps its
   elements in a C++-owned std::vector/std::unordered_map on the malloc heap. The
   collector calls `trace(obj, mark)` while marking the object; the callback
   invokes `mark(ptr)` once per contained GC pointer. `mark` is the GC's internal
   enqueue primitive: non-heap or already-marked pointers are handled/skipped for
   you, so the callback may pass any candidate pointer safely. This lets a native
   container hold ANY GC value (string, object, array, nested container) with zero
   copies and correct lifetime/identity. NULL for ordinary types. */
typedef void (*fw_trace_fn)(void *obj, void (*mark)(void *ptr));

/* Static, one-per-type map of where pointers live. 8-byte aligned so the
   low 3 bits of a pointer to it are free for GC flags. */
typedef struct FWTypeDescriptor {
  const char *name;
  FWKind      kind;

  /* PLAIN */
  uint32_t        num_ptrs;
  const uint32_t *ptr_offsets;      /* byte offsets of pointer fields */

  /* TAGGED */
  uint32_t        tag_offset;       /* byte offset of the i32 tag */
  uint32_t        value_offset;     /* byte offset of the maybe-pointer */
  uint32_t        num_ptr_tags;
  const int32_t  *ptr_tags;         /* tag values meaning "value is a pointer" */

  /* ARRAY */
  const struct FWTypeDescriptor *elem_desc;  /* how to scan one element */
  size_t                         elem_size;  /* bytes per element */

  /* CUSTOM (appended last so existing field offsets are unchanged; codegen
     emits this field too, so the C and LLVM layouts stay byte-identical). */
  fw_trace_fn                    trace;      /* deep-scan hook, or NULL */
} FWTypeDescriptor;

/* Shared, process-wide descriptors for the two most common runtime shapes. */
extern const FWTypeDescriptor fw_blob_desc;  /* raw byte buffers: strings */
extern const FWTypeDescriptor fw_dyn_desc;   /* boxed {i32 tag; i64 value} */

/* Descriptor-word packing (descriptor pointer + mark/pin bits). */
uintptr_t                 fw_word_pack(const FWTypeDescriptor *desc);
const FWTypeDescriptor   *fw_word_desc(uintptr_t word);
int                       fw_word_marked(uintptr_t word);
uintptr_t                 fw_word_set_mark(uintptr_t word);
uintptr_t                 fw_word_clear_mark(uintptr_t word);

typedef struct {
  size_t live_objects;   /* objects currently on the heap */
  size_t live_bytes;     /* payload bytes currently on the heap */
  size_t total_allocs;   /* cumulative allocations since init */
  size_t total_frees;    /* cumulative frees since init */
} FWGCStats;

void       fw_gc_init(void);
void      *fw_gc_alloc(size_t size, const FWTypeDescriptor *desc);
/* Allocate a container backing store: `n` elements described by an ARRAY
   descriptor (whose elem_size and elem_desc are set). */
void *fw_gc_alloc_array(const FWTypeDescriptor *array_desc, size_t n);
void       fw_gc_collect(void);
FWGCStats  fw_gc_stats(void);
void       fw_gc_set_stress(int on);   /* 1 = collect on every alloc */

/* A shadow-stack frame: lists the ADDRESSES of a function's pointer locals.
   Slot-address model: each roots[i] is a void** pointing at a pointer local;
   the GC reads *roots[i] to get that local's current value at collect time.
   Codegen pushes/pops these per function (see M2). */
typedef struct FWFrame {
  struct FWFrame *prev;   /* caller's frame */
  uint32_t        n;      /* number of root slots */
  void          **roots;  /* array of n slot addresses (each a void**) */
} FWFrame;

extern FWFrame *fw_gc_shadow_top;    /* current top frame (NULL when empty) */

void fw_gc_add_root(void **slot);
void fw_gc_remove_root(void **slot);

void fw_gc_register_finalizer(void *obj, void (*fn)(void *));

#ifdef __cplusplus
}
#endif
