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
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA.
 */

#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTernaryExpression/BoundTernaryExpression.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/Type.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {

void IRGenerator::visit(binding::BoundTernaryExpression *ternary_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Ternary Expression", "IR GENERATION");

  auto *builder = m_ir_gen_context.getLLVMBuilder().get();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *current_function = m_ir_gen_context.getCurrentFunction();
  assert(current_function && "Ternary expression must be inside a function");

  types::Type *result_type = ternary_expression->getType().get();
  const bool is_dynamic_result = result_type->isDynamic();

  llvm::Value *dynamic_slot = nullptr;
  if (is_dynamic_result) {
    llvm::Type *llvm_dyn =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(result_type);
    dynamic_slot =
        m_ir_gen_context.createAlloca(llvm_dyn, "ternary.dynamic.result");
  }

  auto *then_block =
      llvm::BasicBlock::Create(*ctx, "ternary.then", current_function);
  auto *else_block =
      llvm::BasicBlock::Create(*ctx, "ternary.else", current_function);
  auto *merge_block =
      llvm::BasicBlock::Create(*ctx, "ternary.merge", current_function);

  // Condition
  ternary_expression->getConditionExpression()->accept(this);
  llvm::Value *resolved = resolveValue(m_last_value, m_last_type);
  llvm::Value *cond_value = getConditionAsBool(resolved, m_last_type);
  clearLast();
  builder->CreateCondBr(cond_value, then_block, else_block);

  // Then branch
  m_ir_gen_context.setInsertPoint(then_block);
  ternary_expression->getTrueExpression()->accept(this);
  llvm::Value *true_val = resolveValue(m_last_value, m_last_type);
  types::Type *true_type = m_last_type;
  clearLast();
  if (is_dynamic_result) {
    emitTypedStore(dynamic_slot, result_type, true_val, true_type);
  }
  if (builder->GetInsertBlock()->getTerminator() == nullptr) {
    m_ir_gen_context.createBranch(merge_block);
  }
  llvm::BasicBlock *then_block_for_phi = builder->GetInsertBlock();

  // Else branch
  m_ir_gen_context.setInsertPoint(else_block);
  ternary_expression->getFalseExpression()->accept(this);
  llvm::Value *false_val = resolveValue(m_last_value, m_last_type);
  types::Type *false_type = m_last_type;
  clearLast();
  if (is_dynamic_result) {
    emitTypedStore(dynamic_slot, result_type, false_val, false_type);
  }
  if (builder->GetInsertBlock()->getTerminator() == nullptr) {
    m_ir_gen_context.createBranch(merge_block);
  }
  llvm::BasicBlock *else_block_for_phi = builder->GetInsertBlock();

  // Merge
  m_ir_gen_context.setInsertPoint(merge_block);
  if (is_dynamic_result) {
    m_last_value = dynamic_slot;
    m_last_type = result_type;
    return;
  }
  if (result_type->isNthg()) {
    // Void-returning branches (e.g. fn() ? a() : b()): no value to merge; LLVM
    // does not allow PHI of void type.
    clearLast();
    return;
  }

  llvm::Type *llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(result_type);
  if (result_type->getKind() == types::TypeKind::kObject) {
    llvm_type = true_val->getType();
  }
  llvm::PHINode *phi = builder->CreatePHI(llvm_type, 2, "ternary.result");
  phi->addIncoming(true_val, then_block_for_phi);
  phi->addIncoming(false_val, else_block_for_phi);

  m_last_value = phi;
  m_last_type = result_type;
}

} // namespace flow_wing::ir_gen
