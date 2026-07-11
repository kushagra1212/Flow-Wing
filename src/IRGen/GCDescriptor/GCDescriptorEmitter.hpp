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

namespace flow_wing {
namespace ir_gen {

/// Compile-time constant that MUST equal `sizeof(FWTypeDescriptor)` in
/// fw-modules/gc/include/fw_gc.h on an LP64 target. The C side already guards
/// its field order with `_Static_assert`s in fw_gc_descriptors.c; this mirror
/// lets codegen assert that the LLVM struct it builds lays out to the very same
/// number of bytes the runtime reads back.
constexpr uint64_t kFWTypeDescriptorAbiSize = 64;

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

  /// Shared BLOB descriptor (`FW_KIND_BLOB`) for raw byte buffers / strings —
  /// no interior pointers. Cached. Returned as `i8*`.
  llvm::Constant *getBlob();

  /// Shared TAGGED descriptor (`FW_KIND_TAGGED`) for boxed dynamic values
  /// `{ i32 tag; i64 value }`. tag_offset=0, value_offset=8, and the pointer
  /// tags are {5, 9, 10} (STRING, OBJECT, ARRAY). Cached. Returned as `i8*`.
  llvm::Constant *getDynamic();

  /// ARRAY descriptor (`FW_KIND_ARRAY`) over an element descriptor. `elem_desc`
  /// points at the PLAIN descriptor for `elem_struct_ty`; `elem_size` is the
  /// caller-supplied per-element byte size. Cached per element struct type.
  /// Returned as `i8*`.
  llvm::Constant *getOrEmitArray(llvm::StructType *elem_struct_ty,
                                 uint64_t elem_size);

private:
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
  llvm::Constant *m_blob = nullptr;
  llvm::Constant *m_dyn = nullptr;
};

} // namespace ir_gen
} // namespace flow_wing
