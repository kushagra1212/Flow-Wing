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
} FWTypeDescriptor;

/* Descriptor-word packing (descriptor pointer + mark/pin bits). */
uintptr_t                 fw_word_pack(const FWTypeDescriptor *desc);
const FWTypeDescriptor   *fw_word_desc(uintptr_t word);
int                       fw_word_marked(uintptr_t word);
uintptr_t                 fw_word_set_mark(uintptr_t word);
uintptr_t                 fw_word_clear_mark(uintptr_t word);

#ifdef __cplusplus
}
#endif
