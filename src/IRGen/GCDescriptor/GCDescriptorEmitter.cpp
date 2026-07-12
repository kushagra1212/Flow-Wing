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

#include "GCDescriptorEmitter.hpp"

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/Constant.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Type.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

namespace flow_wing {
namespace ir_gen {

// FWKind values from fw-modules/gc/include/fw_gc.h. Kept local (rather than
// including the C header) so this translation unit depends only on LLVM.
static constexpr uint32_t kKindPlain = 0;
static constexpr uint32_t kKindBlob = 1;
static constexpr uint32_t kKindTagged = 2;
static constexpr uint32_t kKindArray = 3;

llvm::StructType *GCDescriptorEmitter::descriptorType() {
  if (m_desc_ty)
    return m_desc_ty;

  llvm::Type *i8p = llvm::Type::getInt8PtrTy(*m_ctx);
  llvm::Type *i32 = llvm::Type::getInt32Ty(*m_ctx);
  llvm::Type *i32p = llvm::Type::getInt32PtrTy(*m_ctx);
  llvm::Type *i64 = llvm::Type::getInt64Ty(*m_ctx);

  // Field order MUST mirror `FWTypeDescriptor` exactly:
  //   const char *name;            -> i8*
  //   FWKind      kind;            -> i32 (C enum lowers to int == i32 on LP64)
  //   uint32_t    num_ptrs;        -> i32
  //   const uint32_t *ptr_offsets; -> i32*
  //   uint32_t    tag_offset;      -> i32
  //   uint32_t    value_offset;    -> i32
  //   uint32_t    num_ptr_tags;    -> i32
  //   const int32_t *ptr_tags;     -> i32*
  //   const FWTypeDescriptor *elem_desc; -> i8* (opaque descriptor pointer)
  //   size_t      elem_size;       -> i64 (LP64)
  //   fw_trace_fn trace;           -> i8* (opaque function pointer, or null)
  // A non-packed struct is used deliberately: LLVM's default aggregate layout
  // follows the same platform ABI as C, so the natural padding matches.
  m_desc_ty = llvm::StructType::create(
      *m_ctx, {i8p, i32, i32, i32p, i32, i32, i32, i32p, i8p, i64, i8p},
      "FWTypeDescriptor", /*isPacked=*/false);

  // ABI tripwire: if the emitted layout is not 72 bytes on LP64, one of the
  // element types above is wrong. Fix the element types, not this assert. In
  // release builds NDEBUG strips the assert, so guard against an unused-var
  // warning under -Werror when it compiles out.
  const uint64_t alloc_size =
      m_module->getDataLayout().getTypeAllocSize(m_desc_ty).getFixedValue();
  (void)alloc_size;
  assert(
      alloc_size == kFWTypeDescriptorAbiSize &&
      "FWTypeDescriptor LLVM layout must match the C struct (LP64=72 bytes)");

  return m_desc_ty;
}

llvm::Constant *GCDescriptorEmitter::asI8Ptr(llvm::Constant *ptr) {
  return llvm::ConstantExpr::getBitCast(ptr, llvm::Type::getInt8PtrTy(*m_ctx));
}

llvm::Constant *GCDescriptorEmitter::emitCString(const std::string &text,
                                                 const std::string &name) {
  // NUL-terminated so consumers reading `const char *name` see a valid C
  // string.
  llvm::Constant *str =
      llvm::ConstantDataArray::getString(*m_ctx, text, /*AddNull=*/true);
  auto *g =
      new llvm::GlobalVariable(*m_module, str->getType(), /*isConstant=*/true,
                               llvm::GlobalValue::PrivateLinkage, str, name);
  g->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
  return asI8Ptr(g);
}

// Recursively collect the byte offsets of every GC pointer reachable *inline*
// within `ty`, relative to `base`. Nested inline structs and fixed-size arrays
// are flattened so an object/class with, say, an inline `X[2]` field whose `X`
// holds a string still has that string's slot marked. Self-referential types
// (`next: Node`) are stored by pointer in LLVM, so they terminate the recursion
// at the pointer field rather than expanding forever.
static void collectPointerOffsets(llvm::Type *ty, uint64_t base,
                                  const llvm::DataLayout &dl,
                                  std::vector<uint32_t> &out) {
  if (ty->isPointerTy()) {
    out.push_back(static_cast<uint32_t>(base));
    return;
  }
  if (auto *st = llvm::dyn_cast<llvm::StructType>(ty)) {
    // Boxed dynamic `{ i32 tag; i64 value }`: the payload at offset 8 may hold a
    // GC pointer depending on the tag. It is not statically pointer-typed, so
    // mark the payload slot; fw_gc_resolve_object skips it when the boxed value
    // is not a live heap object, making this over-approximation safe.
    if (st->getName() == "fg_dyn_type") {
      out.push_back(static_cast<uint32_t>(base + 8));
      return;
    }
    const llvm::StructLayout *sl = dl.getStructLayout(st);
    for (unsigned i = 0, n = st->getNumElements(); i < n; ++i)
      collectPointerOffsets(st->getElementType(i),
                            base + sl->getElementOffset(i), dl, out);
    return;
  }
  if (auto *at = llvm::dyn_cast<llvm::ArrayType>(ty)) {
    llvm::Type *el = at->getElementType();
    uint64_t esz = dl.getTypeAllocSize(el);
    for (uint64_t i = 0, n = at->getNumElements(); i < n; ++i)
      collectPointerOffsets(el, base + i * esz, dl, out);
    return;
  }
  // Scalar (int/float/bool/char): no interior pointers.
}

void GCDescriptorEmitter::registerNativeHandleOffset(llvm::StructType *struct_ty,
                                                     uint32_t offset) {
  std::vector<uint32_t> &offs = m_extra_ptr_offsets[struct_ty];
  if (std::find(offs.begin(), offs.end(), offset) == offs.end())
    offs.push_back(offset);
}

llvm::Constant *
GCDescriptorEmitter::getOrEmitPlain(llvm::StructType *struct_ty) {
  auto it = m_plain_cache.find(struct_ty);
  if (it != m_plain_cache.end())
    return it->second;

  llvm::Type *i8p = llvm::Type::getInt8PtrTy(*m_ctx);
  llvm::Type *i32 = llvm::Type::getInt32Ty(*m_ctx);
  llvm::Type *i32p = llvm::Type::getInt32PtrTy(*m_ctx);
  llvm::Type *i64 = llvm::Type::getInt64Ty(*m_ctx);

  // Collect byte offsets of every interior GC pointer (recursing through inline
  // nested structs and arrays) from the DataLayout.
  std::vector<uint32_t> offsets;
  collectPointerOffsets(struct_ty, 0, m_module->getDataLayout(), offsets);
  // Merge any registered native-handle offsets (int64 fields that actually hold
  // a heap pointer, e.g. an FFI wrapper's `_handle`) that the layout scan cannot
  // discover. Dedup so a slot is never listed twice.
  auto extra_it = m_extra_ptr_offsets.find(struct_ty);
  if (extra_it != m_extra_ptr_offsets.end()) {
    for (uint32_t off : extra_it->second) {
      if (std::find(offsets.begin(), offsets.end(), off) == offsets.end())
        offsets.push_back(off);
    }
  }
  std::vector<llvm::Constant *> offset_consts;
  offset_consts.reserve(offsets.size());
  for (uint32_t off : offsets)
    offset_consts.push_back(llvm::ConstantInt::get(i32, off));
  const uint32_t num_ptrs = static_cast<uint32_t>(offset_consts.size());

  const std::string struct_name = struct_ty->getName().str();

  // Emit the `[N x i32]` offsets global (or a null i32* when there are none).
  llvm::Constant *offsets_ptr =
      llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(i32p));
  if (!offset_consts.empty()) {
    auto *arr_ty = llvm::ArrayType::get(i32, offset_consts.size());
    auto *arr = llvm::ConstantArray::get(arr_ty, offset_consts);
    auto *arr_g = new llvm::GlobalVariable(
        *m_module, arr_ty, /*isConstant=*/true,
        llvm::GlobalValue::PrivateLinkage, arr, "__gc_offsets_" + struct_name);
    arr_g->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
    offsets_ptr = llvm::ConstantExpr::getBitCast(arr_g, i32p);
  }

  llvm::Constant *name = emitCString(
      struct_name.empty() ? "plain" : struct_name, "__gc_name_" + struct_name);

  std::vector<llvm::Constant *> fields = {
      name,                                    // name
      llvm::ConstantInt::get(i32, kKindPlain), // kind
      llvm::ConstantInt::get(i32, num_ptrs),   // num_ptrs
      offsets_ptr,                             // ptr_offsets
      llvm::ConstantInt::get(i32, 0),          // tag_offset
      llvm::ConstantInt::get(i32, 0),          // value_offset
      llvm::ConstantInt::get(i32, 0),          // num_ptr_tags
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i32p)), // ptr_tags
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i8p)), // elem_desc
      llvm::ConstantInt::get(i64, 0),          // elem_size
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i8p)), // trace
  };

  auto *init = llvm::ConstantStruct::get(descriptorType(), fields);
  auto *g = new llvm::GlobalVariable(
      *m_module, descriptorType(), /*isConstant=*/true,
      llvm::GlobalValue::PrivateLinkage, init, "__gc_desc_" + struct_name);

  llvm::Constant *as_i8p = asI8Ptr(g);
  m_plain_cache[struct_ty] = as_i8p;
  return as_i8p;
}

llvm::Constant *GCDescriptorEmitter::getBlob() {
  if (m_blob)
    return m_blob;

  llvm::Type *i8p = llvm::Type::getInt8PtrTy(*m_ctx);
  llvm::Type *i32 = llvm::Type::getInt32Ty(*m_ctx);
  llvm::Type *i32p = llvm::Type::getInt32PtrTy(*m_ctx);
  llvm::Type *i64 = llvm::Type::getInt64Ty(*m_ctx);

  llvm::Constant *name = emitCString("blob", "__gc_name_blob");

  std::vector<llvm::Constant *> fields = {
      name,                                   // name
      llvm::ConstantInt::get(i32, kKindBlob), // kind
      llvm::ConstantInt::get(i32, 0),         // num_ptrs
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i32p)), // ptr_offsets
      llvm::ConstantInt::get(i32, 0),           // tag_offset
      llvm::ConstantInt::get(i32, 0),           // value_offset
      llvm::ConstantInt::get(i32, 0),           // num_ptr_tags
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i32p)), // ptr_tags
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i8p)), // elem_desc
      llvm::ConstantInt::get(i64, 0),          // elem_size
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i8p)), // trace
  };

  auto *init = llvm::ConstantStruct::get(descriptorType(), fields);
  auto *g = new llvm::GlobalVariable(
      *m_module, descriptorType(), /*isConstant=*/true,
      llvm::GlobalValue::PrivateLinkage, init, "__gc_blob_desc");

  m_blob = asI8Ptr(g);
  return m_blob;
}

llvm::Constant *GCDescriptorEmitter::getDynamic() {
  if (m_dyn)
    return m_dyn;

  llvm::Type *i8p = llvm::Type::getInt8PtrTy(*m_ctx);
  llvm::Type *i32 = llvm::Type::getInt32Ty(*m_ctx);
  llvm::Type *i32p = llvm::Type::getInt32PtrTy(*m_ctx);
  llvm::Type *i64 = llvm::Type::getInt64Ty(*m_ctx);

  // Boxed dynamic value is `{ i32 tag; i64 value }`: int64 aligns to 8, so 4
  // bytes of padding follow `tag` and `value` sits at offset 8. Pointer tags
  // are STRING=5, OBJECT=9, ARRAY=10 (matching fw_dyn_desc in the runtime).
  std::vector<llvm::Constant *> tag_consts = {
      llvm::ConstantInt::get(i32, static_cast<uint32_t>(5)),
      llvm::ConstantInt::get(i32, static_cast<uint32_t>(9)),
      llvm::ConstantInt::get(i32, static_cast<uint32_t>(10)),
  };
  auto *tags_arr_ty = llvm::ArrayType::get(i32, tag_consts.size());
  auto *tags_arr = llvm::ConstantArray::get(tags_arr_ty, tag_consts);
  auto *tags_g = new llvm::GlobalVariable(
      *m_module, tags_arr_ty, /*isConstant=*/true,
      llvm::GlobalValue::PrivateLinkage, tags_arr, "__gc_dyn_ptr_tags");
  tags_g->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
  llvm::Constant *tags_ptr = llvm::ConstantExpr::getBitCast(tags_g, i32p);

  llvm::Constant *name = emitCString("dynamic", "__gc_name_dynamic");

  std::vector<llvm::Constant *> fields = {
      name,                                     // name
      llvm::ConstantInt::get(i32, kKindTagged), // kind
      llvm::ConstantInt::get(i32, 0),           // num_ptrs
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i32p)), // ptr_offsets
      llvm::ConstantInt::get(i32, 0),           // tag_offset
      llvm::ConstantInt::get(i32, 8),           // value_offset
      llvm::ConstantInt::get(i32, 3),           // num_ptr_tags
      tags_ptr,                                 // ptr_tags
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i8p)), // elem_desc
      llvm::ConstantInt::get(i64, 0),          // elem_size
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i8p)), // trace
  };

  auto *init = llvm::ConstantStruct::get(descriptorType(), fields);
  auto *g = new llvm::GlobalVariable(
      *m_module, descriptorType(), /*isConstant=*/true,
      llvm::GlobalValue::PrivateLinkage, init, "__gc_dyn_desc");

  m_dyn = asI8Ptr(g);
  return m_dyn;
}

llvm::Constant *
GCDescriptorEmitter::getOrEmitArray(llvm::StructType *elem_struct_ty,
                                    uint64_t elem_size) {
  auto it = m_array_cache.find(elem_struct_ty);
  if (it != m_array_cache.end())
    return it->second;

  llvm::Type *i32 = llvm::Type::getInt32Ty(*m_ctx);
  llvm::Type *i32p = llvm::Type::getInt32PtrTy(*m_ctx);
  llvm::Type *i64 = llvm::Type::getInt64Ty(*m_ctx);

  // elem_desc is an i8* in our struct, so the i8* returned by getOrEmitPlain
  // can be stored directly. The boxed dynamic value `{ i32 tag; i64 value }`
  // has no *statically* pointer-typed field (the payload is an i64), so a PLAIN
  // descriptor would mark zero pointers and the boxed string/object/array would
  // be collected. Elements of that shape must be traced with the TAGGED
  // descriptor instead.
  llvm::Constant *elem_desc = elem_struct_ty->getName() == "fg_dyn_type"
                                  ? getDynamic()
                                  : getOrEmitPlain(elem_struct_ty);

  const std::string elem_name = elem_struct_ty->getName().str();
  llvm::Constant *name = emitCString("array", "__gc_name_array_" + elem_name);

  std::vector<llvm::Constant *> fields = {
      name,                                    // name
      llvm::ConstantInt::get(i32, kKindArray), // kind
      llvm::ConstantInt::get(i32, 0),          // num_ptrs
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i32p)), // ptr_offsets
      llvm::ConstantInt::get(i32, 0),           // tag_offset
      llvm::ConstantInt::get(i32, 0),           // value_offset
      llvm::ConstantInt::get(i32, 0),           // num_ptr_tags
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i32p)), // ptr_tags
      elem_desc,                                // elem_desc
      llvm::ConstantInt::get(i64, elem_size),   // elem_size
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(llvm::Type::getInt8PtrTy(*m_ctx))), // trace
  };

  auto *init = llvm::ConstantStruct::get(descriptorType(), fields);
  auto *g = new llvm::GlobalVariable(
      *m_module, descriptorType(), /*isConstant=*/true,
      llvm::GlobalValue::PrivateLinkage, init, "__gc_array_desc_" + elem_name);

  llvm::Constant *as_i8p = asI8Ptr(g);
  m_array_cache[elem_struct_ty] = as_i8p;
  return as_i8p;
}

llvm::Constant *GCDescriptorEmitter::getSinglePointerElem() {
  if (m_single_ptr_elem)
    return m_single_ptr_elem;

  llvm::Type *i8p = llvm::Type::getInt8PtrTy(*m_ctx);
  llvm::Type *i32 = llvm::Type::getInt32Ty(*m_ctx);
  llvm::Type *i32p = llvm::Type::getInt32PtrTy(*m_ctx);
  llvm::Type *i64 = llvm::Type::getInt64Ty(*m_ctx);

  // A single pointer sits at byte offset 0 of the element slot.
  auto *offsets_arr_ty = llvm::ArrayType::get(i32, 1);
  auto *offsets_arr = llvm::ConstantArray::get(
      offsets_arr_ty, {llvm::ConstantInt::get(i32, 0)});
  auto *offsets_g = new llvm::GlobalVariable(
      *m_module, offsets_arr_ty, /*isConstant=*/true,
      llvm::GlobalValue::PrivateLinkage, offsets_arr, "__gc_offsets_ptr_elem");
  offsets_g->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
  llvm::Constant *offsets_ptr = llvm::ConstantExpr::getBitCast(offsets_g, i32p);

  llvm::Constant *name = emitCString("ptr_elem", "__gc_name_ptr_elem");

  std::vector<llvm::Constant *> fields = {
      name,                                    // name
      llvm::ConstantInt::get(i32, kKindPlain), // kind
      llvm::ConstantInt::get(i32, 1),          // num_ptrs
      offsets_ptr,                             // ptr_offsets
      llvm::ConstantInt::get(i32, 0),          // tag_offset
      llvm::ConstantInt::get(i32, 0),          // value_offset
      llvm::ConstantInt::get(i32, 0),          // num_ptr_tags
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i32p)), // ptr_tags
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i8p)), // elem_desc
      llvm::ConstantInt::get(i64, 0),          // elem_size
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i8p)), // trace
  };

  auto *init = llvm::ConstantStruct::get(descriptorType(), fields);
  auto *g = new llvm::GlobalVariable(
      *m_module, descriptorType(), /*isConstant=*/true,
      llvm::GlobalValue::PrivateLinkage, init, "__gc_desc_ptr_elem");

  m_single_ptr_elem = asI8Ptr(g);
  return m_single_ptr_elem;
}

llvm::Constant *GCDescriptorEmitter::getOrEmitArrayOfPointer(uint64_t elem_size) {
  if (m_array_ptr)
    return m_array_ptr;

  llvm::Type *i32 = llvm::Type::getInt32Ty(*m_ctx);
  llvm::Type *i32p = llvm::Type::getInt32PtrTy(*m_ctx);
  llvm::Type *i64 = llvm::Type::getInt64Ty(*m_ctx);

  llvm::Constant *elem_desc = getSinglePointerElem();
  llvm::Constant *name = emitCString("array_ptr", "__gc_name_array_ptr");

  std::vector<llvm::Constant *> fields = {
      name,                                    // name
      llvm::ConstantInt::get(i32, kKindArray), // kind
      llvm::ConstantInt::get(i32, 0),          // num_ptrs
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i32p)), // ptr_offsets
      llvm::ConstantInt::get(i32, 0),           // tag_offset
      llvm::ConstantInt::get(i32, 0),           // value_offset
      llvm::ConstantInt::get(i32, 0),           // num_ptr_tags
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(i32p)), // ptr_tags
      elem_desc,                                // elem_desc
      llvm::ConstantInt::get(i64, elem_size),   // elem_size
      llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(llvm::Type::getInt8PtrTy(*m_ctx))), // trace
  };

  auto *init = llvm::ConstantStruct::get(descriptorType(), fields);
  auto *g = new llvm::GlobalVariable(
      *m_module, descriptorType(), /*isConstant=*/true,
      llvm::GlobalValue::PrivateLinkage, init, "__gc_array_desc_ptr");

  m_array_ptr = asI8Ptr(g);
  return m_array_ptr;
}

} // namespace ir_gen
} // namespace flow_wing
