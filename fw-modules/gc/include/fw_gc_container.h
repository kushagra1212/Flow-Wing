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

/* Helpers for FFI modules whose native container (std::vector / std::map / ...)
   holds boxed dynamic values on the C++ heap, which the precise GC cannot scan.
   Such a module gives its handle a BLOB descriptor with a `trace` hook and marks
   each contained GC pointer from that hook. These helpers factor out the two
   bits every such module needs identically. */

#pragma once
#include "fw_gc.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Tags of a boxed dynamic value whose `value` word is a GC heap pointer, mirror
   of fw_dyn_desc's ptr_tags: STRING=5, OBJECT=9, ARRAY=10. A container trace
   hook marks an element iff its tag satisfies this. */
static inline int fw_dyn_tag_is_gc_ptr(int32_t tag) {
  return tag == 5 || tag == 9 || tag == 10;
}

/* Build a BLOB descriptor augmented with a deep-scan `trace` hook. The container
   struct itself carries no GC-visible pointer (its backing store is malloc/new
   memory), so BLOB is correct for the layout scan; `trace` reaches the elements.
   Returned by value — store it in a `static const` at the call site. memset so
   every unnamed field is zero (C++17 has no designated initializers). */
static inline FWTypeDescriptor fw_make_container_desc(const char *name,
                                                      fw_trace_fn trace) {
  FWTypeDescriptor d;
  memset(&d, 0, sizeof(d));
  d.name = name;
  d.kind = FW_KIND_BLOB;
  d.trace = trace;
  return d;
}

#ifdef __cplusplus
}
#endif
