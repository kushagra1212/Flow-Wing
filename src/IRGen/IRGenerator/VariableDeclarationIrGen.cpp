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

#include "src/IRGen/IRGenerator/IRGenHelper/DynamicValueHandler.h"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/common/types/Type.hpp"
#include "src/utils/LogConfig.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Instructions.h"

namespace flow_wing::ir_gen {

namespace {

// Recursively collects the byte offsets of every heap-pointer leaf within an
// aggregate stack type, relative to `base`. Used to root the individual pointer
// fields of a multi-return `ret_slot` (which packs its results inline, so the
// single-word per-alloca root model cannot reach nested pointers). Non-pointer
// leaves are skipped; the runtime's fw_gc_resolve_object guard makes any stray
// offset harmless regardless.
void collectPointerLeafOffsets(llvm::Type *type, const llvm::DataLayout &dl,
                               uint64_t base, std::vector<uint64_t> &out) {
  if (type->isPointerTy()) {
    out.push_back(base);
    return;
  }
  if (auto *st = llvm::dyn_cast<llvm::StructType>(type)) {
    const llvm::StructLayout *sl = dl.getStructLayout(st);
    for (unsigned i = 0; i < st->getNumElements(); ++i)
      collectPointerLeafOffsets(st->getElementType(i), dl,
                                base + sl->getElementOffset(i), out);
    return;
  }
  if (auto *at = llvm::dyn_cast<llvm::ArrayType>(type)) {
    llvm::Type *el = at->getElementType();
    uint64_t stride = dl.getTypeAllocSize(el);
    for (uint64_t k = 0; k < at->getNumElements(); ++k)
      collectPointerLeafOffsets(el, dl, base + k * stride, out);
    return;
  }
}
// Registers `storage_ptr` as a per-function GC root iff it is a stack alloca.
// For every GC-reference-typed local the runtime value is a single heap pointer
// stored at offset 0 of the alloca: class/string locals and object/class/string
// params are `ptr` allocas, while object/array locals are stored as a heap
// pointer too but their alloca is typed as the object struct / array (e.g.
// `alloca %Point` / `alloca %Node`, which may be wider than a pointer). The
// runtime marker reads only the first word, so a struct-typed alloca whose first
// word holds the heap pointer is rooted correctly regardless of its total size.
// Reading a non-heap first word (a genuinely inline aggregate) is harmless: the
// runtime's fw_gc_resolve_object heap-membership guard skips it.
// A dynamic local is boxed inline as `%fg_dyn_type { i32 tag; i64 value }`; its
// value field may hold a GC string/object/array pointer. Such locals must be
// rooted too — e.g. `var combined = a + b` infers `dynamic`, and the boxed
// string is otherwise collected at the next allocation. The shadow-frame emitter
// recognises an `fg_dyn_type` alloca and roots its payload slot (offset 8), and
// fw_gc_resolve_object skips non-pointer payloads, so this is always safe.
void maybeRegisterGcRoot(IRGenContext &ctx, const types::Type *var_type,
                         llvm::Value *storage_ptr) {
  if (var_type == nullptr)
    return;
  if (!var_type->isGcReference() && !var_type->isDynamic())
    return;
  if (auto *alloca = llvm::dyn_cast_or_null<llvm::AllocaInst>(storage_ptr))
    ctx.addGcRootAlloca(alloca);
}
} // namespace

void IRGenerator::rootMultiReturnSlotLeaves(llvm::Value *struct_ptr,
                                            llvm::Type *struct_type) {
  auto *ret_alloca = llvm::dyn_cast_or_null<llvm::AllocaInst>(struct_ptr);
  if (!ret_alloca || struct_type == nullptr)
    return;
  const llvm::DataLayout &dl = m_ir_gen_context.getLLVMModule()->getDataLayout();
  std::vector<uint64_t> leaf_offsets;
  collectPointerLeafOffsets(struct_type, dl, 0, leaf_offsets);
  for (uint64_t off : leaf_offsets)
    m_ir_gen_context.addGcRootSlot(ret_alloca, off);
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundVariableDeclaration *variable_declaration) {
  CODEGEN_DEBUG_LOG("Visiting Bound Variable Declaration", "IR GENERATION");

  const auto &symbols = variable_declaration->getSymbols();
  const auto &multi_exprs = variable_declaration->getInitializerExpressions();
  auto &builder = m_ir_gen_context.getLLVMBuilder();

  size_t var_idx = 0;
  size_t expr_idx = 0;

  while (var_idx < symbols.size()) {
    if (expr_idx < multi_exprs.size() && multi_exprs[expr_idx] != nullptr &&
        multi_exprs[expr_idx]->isMultipleType()) {
      auto &expr = multi_exprs[expr_idx];
      expr->accept(this);

      assert(m_last_value &&
             "m_last_value is null after initializer expression");
      llvm::Value *struct_ptr = m_last_value;
      llvm::Type *struct_type = m_last_llvm_type;

      // Root every heap-pointer leaf packed inline in the multi-return slot so
      // that results produced by the call survive the fw_gc_alloc safepoints
      // that the field-by-field unpack below performs (each destination heap
      // array/object is freshly allocated). Without this, a later field's
      // strings/objects are freed while an earlier field is being copied.
      rootMultiReturnSlotLeaves(struct_ptr, struct_type);

      size_t num_returns = expr->getMultipleTypes().size();
      for (size_t i = 0; i < num_returns; ++i) {
        if (var_idx >= symbols.size())
          break;

        const auto &variable_symbol =
            static_cast<const analysis::VariableSymbol *>(
                symbols[var_idx].get());

        CODEGEN_DEBUG_LOG("Variable Symbol (Multi)",
                          variable_symbol->getName());

        auto *var_type = variable_symbol->getType().get();
        auto *llvm_type =
            m_ir_gen_context.getTypeBuilder()->getLLVMType(var_type);

        auto source_tuple_types = expr->getMultipleTypes();
        auto *source_field_type = source_tuple_types[i].get();
        auto *source_llvm_type =
            m_ir_gen_context.getTypeBuilder()->getLLVMType(source_field_type);

        if (source_field_type->getKind() == types::TypeKind::kClass ||
            source_field_type->getKind() == types::TypeKind::kObject) {
          source_llvm_type = source_llvm_type->getPointerTo();
        }

        if (var_type->getKind() == types::TypeKind::kClass) {
          llvm_type = llvm_type->getPointerTo();
        }
        // For module-top globals `getQualifiedName()` is `<module>.<name>` so
        // it matches the key set by `GlobalDeclarationsInitializer`; for
        // locals it falls back to the bare name.
        const std::string storage_key = variable_symbol->getQualifiedName();
        llvm::Value *storage_ptr = nullptr;

        if (m_ir_gen_context.isGlobalScope()) {
          llvm::Value *existing_global_variable =
              m_ir_gen_context.getSymbol(storage_key);
          if (existing_global_variable &&
              llvm::isa<llvm::GlobalVariable>(existing_global_variable)) {
            storage_ptr = existing_global_variable;
          }
        }

        if (!storage_ptr) {
          storage_ptr = m_ir_gen_context.createAlloca(
              llvm_type, variable_symbol->getName());
          m_ir_gen_context.setSymbol(storage_key, storage_ptr);
          maybeRegisterGcRoot(m_ir_gen_context, var_type, storage_ptr);
        }

        llvm::Value *gep = builder->CreateStructGEP(
            struct_type, struct_ptr, static_cast<unsigned>(i),
            "extract_" + variable_symbol->getName());
        llvm::Value *extracted_val = builder->CreateLoad(
            source_llvm_type, gep, "load_" + variable_symbol->getName());

        emitTypedStore(storage_ptr, var_type, extracted_val, source_field_type);
        var_idx++;
      }
    } else {
      const auto &variable_symbol =
          static_cast<const analysis::VariableSymbol *>(symbols[var_idx].get());

      CODEGEN_DEBUG_LOG("Variable Symbol (Single)", variable_symbol->getName());

      auto *var_type = variable_symbol->getType().get();
      auto *llvm_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(var_type);
      if (var_type->getKind() == types::TypeKind::kClass) {
        llvm_type = llvm_type->getPointerTo();
      }
      const std::string storage_key = variable_symbol->getQualifiedName();
      llvm::Value *storage_ptr = nullptr;

      if (m_ir_gen_context.isGlobalScope()) {
        llvm::Value *existing_global_variable =
            m_ir_gen_context.getSymbol(storage_key);
        if (existing_global_variable &&
            llvm::isa<llvm::GlobalVariable>(existing_global_variable)) {
          storage_ptr = existing_global_variable;
        }
      }

      if (!storage_ptr) {
        storage_ptr = m_ir_gen_context.createAlloca(llvm_type,
                                                    variable_symbol->getName());
        m_ir_gen_context.setSymbol(storage_key, storage_ptr);
        maybeRegisterGcRoot(m_ir_gen_context, var_type, storage_ptr);
      }

      auto *init_expression = variable_symbol->getInitializerExpression().get();
      if (init_expression) {
        init_expression->accept(this);
        assert(m_last_value &&
               "m_last_value is null after initializer expression");

        emitTypedStore(storage_ptr, var_type, m_last_value, m_last_type);

        CODEGEN_DEBUG_LOG("After emit ", " ");
      }
      var_idx++;
    }

    expr_idx++;
    clearLast();
  }
}
} // namespace flow_wing::ir_gen
