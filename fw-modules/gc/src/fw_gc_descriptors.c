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
#include <stddef.h>

/* Layout tripwire: these shared descriptors use designated initializers, but
   the conservative reader and codegen also index fields by offset, so the
   struct field order must match what the runtime assumes. If either assert
   fires, the FWTypeDescriptor field order changed and this file (and callers)
   must be revisited. */
_Static_assert(offsetof(FWTypeDescriptor, kind) == sizeof(void *),
               "FWTypeDescriptor.kind must follow the leading name pointer");
_Static_assert(offsetof(FWTypeDescriptor, num_ptrs) == sizeof(void *) + sizeof(int),
               "FWTypeDescriptor.num_ptrs must follow name + kind");

/* Raw byte buffer: no interior pointers (e.g. string storage). */
const FWTypeDescriptor fw_blob_desc = {
  .name = "blob",
  .kind = FW_KIND_BLOB,
};

/* Boxed dynamic value: C shape is `{ int32_t tag; int64_t value; }`. int64
   aligns to 8, so 4 bytes of padding sit after `tag` and `value` lives at
   offset 8. Tags that mean "value is a heap pointer": STRING=5, OBJECT=9,
   ARRAY=10. */
static const int32_t fw_dyn_ptr_tags[3] = { 5, 9, 10 };

const FWTypeDescriptor fw_dyn_desc = {
  .name = "dynamic",
  .kind = FW_KIND_TAGGED,
  .tag_offset = 0,
  .value_offset = 8,
  .num_ptr_tags = 3,
  .ptr_tags = fw_dyn_ptr_tags,
};
