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

#include "src/IRGen/IRGenerator/IRGenerator.hpp"

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

#include <vector>

namespace flow_wing {
namespace ir_gen {

// Mirrors the runtime C struct `FWFrame { FWFrame* prev; uint32_t n;
// void** roots; }` (fw-modules/gc/include/fw_gc.h) as an LLVM identified
// struct. Created once per module and reused.
llvm::StructType *IRGenerator::getOrCreateFWFrameType() {
  auto &ctx = *m_ir_gen_context.getLLVMContext();
  if (auto *existing = llvm::StructType::getTypeByName(ctx, "FWFrame"))
    return existing;
  auto *frameTy = llvm::StructType::create(ctx, "FWFrame");
  llvm::Type *i8ptr = llvm::Type::getInt8PtrTy(ctx);
  frameTy->setBody({llvm::PointerType::getUnqual(frameTy),
                    llvm::Type::getInt32Ty(ctx),
                    llvm::PointerType::getUnqual(i8ptr)});
  return frameTy;
}

// Declares (or returns) the external `fw_gc_shadow_top` global, the head of the
// shadow-stack frame list that the runtime marker walks. Resolved by the linker
// in AOT and by JITRuntimeSymbols.def in JIT.
llvm::GlobalVariable *
IRGenerator::getOrCreateGcShadowTop(llvm::StructType *frameTy) {
  auto *mod = m_ir_gen_context.getLLVMModule();
  if (auto *g = mod->getGlobalVariable("fw_gc_shadow_top"))
    return g;
  auto *ptrTy = llvm::PointerType::getUnqual(frameTy);
  return new llvm::GlobalVariable(*mod, ptrTy, false,
                                  llvm::GlobalValue::ExternalLinkage, nullptr,
                                  "fw_gc_shadow_top");
}

// Returns N if `ty` is an inline `[N x %fg_dyn_type]` (a by-value array of boxed
// dynamics), else 0. Shared by the shadow-frame emitter (which roots each
// element's payload) and function-parameter registration (which decides whether
// to register the stack copy as a root).
uint32_t IRGenerator::dynArrayElemCount(llvm::Type *ty) {
  if (auto *at = llvm::dyn_cast<llvm::ArrayType>(ty))
    if (auto *st = llvm::dyn_cast<llvm::StructType>(at->getElementType()))
      if (st->hasName() && st->getName() == "fg_dyn_type")
        return static_cast<uint32_t>(at->getNumElements());
  return 0;
}

// Emits the per-function shadow frame: a prologue that builds an array of the
// pointer roots' slot addresses, pushes a frame onto @fw_gc_shadow_top, and an
// epilogue before every `ret` that pops the frame (restores frame.prev).
void IRGenerator::emitGcShadowFrame(llvm::Function *fn) {
  // Snapshot then clear the per-function root list so roots never leak into a
  // subsequently-emitted function (e.g. `main` after a nested function whose
  // definition runs inside main's top-level statement loop).
  std::vector<llvm::AllocaInst *> roots = m_ir_gen_context.getGcRootAllocas();
  std::vector<std::pair<llvm::AllocaInst *, uint64_t>> slots =
      m_ir_gen_context.getGcRootSlots();
  m_ir_gen_context.clearGcRootAllocas();
  if (roots.empty() && slots.empty())
    return;
  auto &ctx = *m_ir_gen_context.getLLVMContext();
  llvm::StructType *frameTy = getOrCreateFWFrameType();
  llvm::GlobalVariable *shadowTop = getOrCreateGcShadowTop(frameTy);
  auto *framePtrTy = llvm::PointerType::getUnqual(frameTy);
  llvm::Type *i8ptr = llvm::Type::getInt8PtrTy(ctx);
  llvm::Type *i8ty = llvm::Type::getInt8Ty(ctx);

  // An inline array of boxed dynamics (`[N x %fg_dyn_type]`) contributes one
  // root per element (each has its own maybe-pointer payload); every other root
  // alloca contributes a single root.
  uint32_t n = static_cast<uint32_t>(slots.size());
  for (auto *r : roots) {
    uint32_t len = dynArrayElemCount(r->getAllocatedType());
    n += (len ? len : 1u);
  }
  auto *arrTy = llvm::ArrayType::get(i8ptr, n);

  // Insert the prologue right after the entry block's alloca run so the frame
  // and roots array are themselves stack-allocated once and dominate the body.
  llvm::BasicBlock &entry = fn->getEntryBlock();
  llvm::BasicBlock::iterator ip = entry.getFirstInsertionPt();
  while (ip != entry.end() && llvm::isa<llvm::AllocaInst>(*ip))
    ++ip;
  llvm::IRBuilder<> pb(&entry, ip);

  llvm::AllocaInst *rootsArr = pb.CreateAlloca(arrTy, nullptr, "__gc_roots");
  uint32_t idx = 0;
  for (uint32_t i = 0; i < roots.size(); ++i) {
    llvm::Type *allocTy = roots[i]->getAllocatedType();
    // Inline array of dynamics: root each element's payload field.
    if (uint32_t len = dynArrayElemCount(allocTy)) {
      auto *fgDynTy = llvm::cast<llvm::StructType>(
          llvm::cast<llvm::ArrayType>(allocTy)->getElementType());
      for (uint32_t k = 0; k < len; ++k) {
        llvm::Value *elem =
            pb.CreateConstInBoundsGEP2_32(allocTy, roots[i], 0, k);
        llvm::Value *payload =
            pb.CreateStructGEP(fgDynTy, elem, 1, "dyn_arr_payload");
        llvm::Value *gep =
            pb.CreateConstInBoundsGEP2_32(arrTy, rootsArr, 0, idx++);
        pb.CreateStore(pb.CreateBitCast(payload, i8ptr), gep);
      }
      continue;
    }
    // Dynamic locals are boxed inline (`%fg_dyn_type = { i32 tag, i64 value }`);
    // reading the box base as a pointer would see the tag word, not the payload.
    // Register the payload field's address instead so a boxed string/object/array
    // is traced. Non-pointer payloads (int/float) are filtered by the runtime's
    // fw_gc_resolve_object heap-membership guard, so this over-approximation is
    // safe.
    llvm::Value *slot_addr = roots[i];
    if (auto *st = llvm::dyn_cast<llvm::StructType>(allocTy)) {
      if (st->hasName() && st->getName() == "fg_dyn_type")
        slot_addr = pb.CreateStructGEP(st, roots[i], 1, "dyn_root_payload");
    }
    llvm::Value *gep = pb.CreateConstInBoundsGEP2_32(arrTy, rootsArr, 0, idx++);
    pb.CreateStore(pb.CreateBitCast(slot_addr, i8ptr), gep);
  }
  // Append the (base, byte-offset) root slots: each addresses a single heap
  // pointer leaf inside a wider stack aggregate (e.g. a multi-return ret_slot).
  for (uint32_t j = 0; j < slots.size(); ++j) {
    llvm::Value *gep = pb.CreateConstInBoundsGEP2_32(arrTy, rootsArr, 0, idx++);
    llvm::Value *leaf = pb.CreateInBoundsGEP(
        i8ty, slots[j].first, pb.getInt64(slots[j].second), "gc_root_leaf");
    pb.CreateStore(leaf, gep);
  }
  llvm::AllocaInst *frame = pb.CreateAlloca(frameTy, nullptr, "__gc_frame");
  llvm::Value *oldTop = pb.CreateLoad(framePtrTy, shadowTop);
  pb.CreateStore(oldTop, pb.CreateStructGEP(frameTy, frame, 0));
  pb.CreateStore(pb.getInt32(n), pb.CreateStructGEP(frameTy, frame, 1));
  pb.CreateStore(pb.CreateConstInBoundsGEP2_32(arrTy, rootsArr, 0, 0),
                 pb.CreateStructGEP(frameTy, frame, 2));
  pb.CreateStore(frame, shadowTop);

  for (llvm::BasicBlock &bb : *fn) {
    auto *term = bb.getTerminator();
    if (term && llvm::isa<llvm::ReturnInst>(term)) {
      llvm::IRBuilder<> rb(term);
      llvm::Value *prev =
          rb.CreateLoad(framePtrTy, rb.CreateStructGEP(frameTy, frame, 0));
      rb.CreateStore(prev, shadowTop);
    }
  }
}

// Spills a freshly-produced GC pointer into a named alloca and registers that
// alloca as a root. Defined here for the next task (temp/SSA spilling); unused
// for now but harmless as a member function.
llvm::AllocaInst *IRGenerator::spillToRoot(llvm::Value *gcPtr,
                                           const std::string &name) {
  llvm::AllocaInst *slot = m_ir_gen_context.createAlloca(gcPtr->getType(), name);
  m_ir_gen_context.getLLVMBuilder()->CreateStore(gcPtr, slot);
  m_ir_gen_context.addGcRootAlloca(slot);
  return slot;
}

} // namespace ir_gen
} // namespace flow_wing
