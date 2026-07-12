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

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace flow_wing {
namespace ir_gen {

/// Compile-time constant that MUST equal `sizeof(FWTypeDescriptor)` in
/// fw-modules/gc/include/fw_gc.h on an LP64 target. The C side already guards
/// its field order with `_Static_assert`s in fw_gc_descriptors.c; this mirror
/// lets codegen assert that the LLVM struct it builds lays out to the very same
/// number of bytes the runtime reads back.
constexpr uint64_t kFWTypeDescriptorAbiSize = 72;

/// Emits `FWTypeDescriptor` LLVM global constants whose in-memory layout
/// matches the C struct in fw-modules/gc/include/fw_gc.h byte-for-byte, and
/// hands back an `i8*` suitable for passing as the descriptor argument of the
/// precise GC's allocation entry points.
///
/// Phase B is purely additive: NOTHING calls this emitter yet, so constructing
/// it or invoking its methods has no effect on emitted program behavior.
/// Descriptors are cached (per LLVM struct type for PLAIN / ARRAY, and once
/// each for the shared BLOB / TAGGED shapes) so repeated requests reuse the
/// same global.
class GCDescriptorEmitter {
public:
  GCDescriptorEmitter(llvm::Module *module, llvm::LLVMContext *ctx)
      : m_module(module), m_ctx(ctx) {}

  /// The LLVM struct type mirroring `FWTypeDescriptor` (created once, cached).
  /// Element types: { i8*, i32, i32, i32*, i32, i32, i32, i32*, i8*, i64 }.
  llvm::StructType *descriptorType();

  /// PLAIN descriptor (`FW_KIND_PLAIN`) for an object/class struct. Pointer
  /// field byte offsets are computed from the module's DataLayout. Cached per
  /// `struct_ty`. Returned as `i8*`.
  llvm::Constant *getOrEmitPlain(llvm::StructType *struct_ty);

  /// Register an additional GC-pointer byte offset for `struct_ty` that the
  /// DataLayout-based scan cannot discover on its own. Used for FFI wrapper
  /// classes whose native handle is stored in an `int64` field that actually
  /// holds a `fw_gc_alloc`'d heap pointer (e.g. `Vec._handle`). Marking the slot
  /// makes the GC keep the handle alive for the wrapper's lifetime and finalize
  /// it on drop; the runtime's fw_gc_resolve_object heap-membership guard makes a
  /// non-heap value (an unset `0` handle) harmless. Must be called before the
  /// first `getOrEmitPlain(struct_ty)` so the offset lands in the cached
  /// descriptor. Idempotent per (struct_ty, offset).
  void registerNativeHandleOffset(llvm::StructType *struct_ty, uint32_t offset);

  /// Shared BLOB descriptor (`FW_KIND_BLOB`) for raw byte buffers / strings —
  /// no interior pointers. Cached. Returned as `i8*`.
  llvm::Constant *getBlob();

  /// Shared TAGGED descriptor (`FW_KIND_TAGGED`) for boxed dynamic values
  /// `{ i32 tag; i64 value }`. tag_offset=0, value_offset=8, and the pointer
  /// tags are {5, 9, 10} (STRING, OBJECT, ARRAY). Cached. Returned as `i8*`.
  llvm::Constant *getDynamic();

  /// ARRAY descriptor (`FW_KIND_ARRAY`) over an element descriptor. `elem_desc`
  /// points at the PLAIN descriptor for `elem_struct_ty` — except for the boxed
  /// dynamic struct (`fg_dyn_type`), where the shared TAGGED descriptor is used
  /// so that boxed pointers inside each element are traced. `elem_size` is the
  /// caller-supplied per-element byte size. Cached per element struct type.
  /// Returned as `i8*`.
  llvm::Constant *getOrEmitArray(llvm::StructType *elem_struct_ty,
                                 uint64_t elem_size);

  /// ARRAY descriptor whose elements are bare GC pointers (e.g. `str[]`, or the
  /// pointer slots of an array of arrays). The element descriptor is a PLAIN
  /// shape with a single pointer at offset 0. `elem_size` is the pointer size
  /// (8 on LP64). Cached (one shared instance). Returned as `i8*`.
  llvm::Constant *getOrEmitArrayOfPointer(uint64_t elem_size);

private:
  /// PLAIN descriptor describing a single pointer at offset 0 (used as the
  /// element descriptor of a pointer-element array). Cached.
  llvm::Constant *getSinglePointerElem();

  /// Bitcast any constant pointer to `i8*` (a no-op under opaque pointers, but
  /// kept explicit to match the codebase's typed-pointer idiom).
  llvm::Constant *asI8Ptr(llvm::Constant *ptr);

  /// Emit (or reuse) a private, constant, NUL-terminated C-string global and
  /// return it bitcast to `i8*`. Used for the descriptor `name` label.
  llvm::Constant *emitCString(const std::string &text, const std::string &name);

  llvm::Module *m_module;
  llvm::LLVMContext *m_ctx;
  llvm::StructType *m_desc_ty = nullptr;
  std::unordered_map<llvm::StructType *, llvm::Constant *> m_plain_cache;
  std::unordered_map<llvm::StructType *, llvm::Constant *> m_array_cache;
  /// Extra GC-pointer byte offsets per struct that the layout scan can't infer
  /// (native handles stored in int64 fields). Consulted by getOrEmitPlain.
  std::unordered_map<llvm::StructType *, std::vector<uint32_t>>
      m_extra_ptr_offsets;
  llvm::Constant *m_blob = nullptr;
  llvm::Constant *m_dyn = nullptr;
  llvm::Constant *m_array_ptr = nullptr;
  llvm::Constant *m_single_ptr_elem = nullptr;
};

} // namespace ir_gen
} // namespace flow_wing
