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

#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/IRGenerator/IRGenHelper/DynamicValueHandler.h"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryOperator/BoundBinaryOperator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/common/types/Type.hpp"
#include "src/utils/LogConfig.h"
#include "llvm/IR/IRBuilder.h"

namespace flow_wing::ir_gen {

llvm::Value *IRGenerator::getBinaryResult(llvm::Value *left_value,
                                          llvm::Value *right_value,
                                          lexer::TokenKind operator_kind,
                                          types::Type *left_type,
                                          types::Type *right_type,
                                          types::Type *result_type) {

  // Handle dynamic type result
  if (result_type->isDynamic()) {
    return getDynamicBinaryResult(left_value, right_value, operator_kind,
                                  left_type, right_type);
  }

  if (result_type == analysis::Builtins::m_bool_type_instance.get()) {

    return getBooleanResult(left_value, right_value, operator_kind, left_type,
                            right_type);
  }

  if (result_type == analysis::Builtins::m_int32_type_instance.get()) {
    return getInt32Result(left_value, right_value, operator_kind, left_type,
                          right_type);
  } else if (result_type == analysis::Builtins::m_int64_type_instance.get()) {
    return getInt64Result(left_value, right_value, operator_kind, left_type,
                          right_type);
  } else if (result_type == analysis::Builtins::m_int8_type_instance.get()) {
    return getInt8Result(left_value, right_value, operator_kind, left_type,
                         right_type);
  }

  if (result_type == analysis::Builtins::m_char_type_instance.get()) {
    return getCharResult(left_value, right_value, operator_kind);
  }

  if (result_type == analysis::Builtins::m_deci32_type_instance.get()) {
    return getDecimal32Result(left_value, right_value, operator_kind);
  }

  if (result_type == analysis::Builtins::m_deci_type_instance.get()) {
    return getDecimalResult(left_value, right_value, operator_kind);
  }

  if (result_type == analysis::Builtins::m_str_type_instance.get()) {
    return getStringResult(left_value, right_value, operator_kind, left_type,
                           right_type);
  }

  assert(false && "Unsupported binary operator");
  return nullptr;
}

void IRGenerator::visit(binding::BoundBinaryExpression *binary_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Binary Expression", "IR GENERATION");

  auto binary_operator = binary_expression->getBinaryOperator();
  auto binary_operator_kind = binary_operator->getSyntaxKind();
  auto result_type = binary_operator->getResultType().get();

  // Short-circuit evaluation for && and ||:
  if (binary_operator_kind == lexer::TokenKind::kAmpersandAmpersandToken ||
      binary_operator_kind == lexer::TokenKind::kPipePipeToken) {
    llvm::Function *current_fn = m_ir_gen_context.getCurrentFunction();
    if (!current_fn) {

      binary_expression->getLeft()->accept(this);
      assert(m_last_value && "m_last_value is null");
      llvm::Value *left_value = m_last_value;
      types::Type *left_type = m_last_type;
      clearLast();
      binary_expression->getRight()->accept(this);
      assert(m_last_value && "m_last_value is null");
      llvm::Value *right_value = m_last_value;
      types::Type *right_type = m_last_type;
      clearLast();
      if (!left_type->isDynamic())
        left_value = resolveValue(left_value, left_type);
      if (!right_type->isDynamic())
        right_value = resolveValue(right_value, right_type);
      auto res = getBooleanResult(left_value, right_value, binary_operator_kind,
                                  binary_operator->getLeftType().get(),
                                  binary_operator->getRightType().get());
      m_last_type = result_type;
      m_last_value = res;
      return;
    }

    auto *ctx = m_ir_gen_context.getLLVMContext();
    auto *builder = m_ir_gen_context.getLLVMBuilder().get();
    bool is_and =
        (binary_operator_kind == lexer::TokenKind::kAmpersandAmpersandToken);

    binary_expression->getLeft()->accept(this);
    assert(m_last_value && "m_last_value is null");
    llvm::Value *left_value = m_last_value;
    types::Type *left_type = m_last_type;
    clearLast();
    if (!left_type->isDynamic())
      left_value = resolveValue(left_value, left_type);
    llvm::Value *left_bool = getConditionAsBool(left_value, left_type);

    llvm::BasicBlock *short_circuit_block =
        llvm::BasicBlock::Create(*ctx, "short_circuit", current_fn);
    llvm::BasicBlock *eval_right_block =
        llvm::BasicBlock::Create(*ctx, "eval_right", current_fn);
    llvm::BasicBlock *merge_block =
        llvm::BasicBlock::Create(*ctx, "logical_merge", current_fn);

    if (is_and) {
      // && : if left is false, short-circuit to false; else evaluate right
      builder->CreateCondBr(left_bool, eval_right_block, short_circuit_block);
    } else {
      // || : if left is true, short-circuit to true; else evaluate right
      builder->CreateCondBr(left_bool, short_circuit_block, eval_right_block);
    }

    m_ir_gen_context.setInsertPoint(short_circuit_block);
    m_ir_gen_context.createBranch(merge_block);

    m_ir_gen_context.setInsertPoint(eval_right_block);
    binary_expression->getRight()->accept(this);
    assert(m_last_value && "m_last_value is null");
    llvm::Value *right_value = m_last_value;
    types::Type *right_type = m_last_type;
    clearLast();
    if (!right_type->isDynamic())
      right_value = resolveValue(right_value, right_type);
    llvm::Value *right_bool = getConditionAsBool(right_value, right_type);
    llvm::BasicBlock *right_exit_block = builder->GetInsertBlock();
    m_ir_gen_context.createBranch(merge_block);

    m_ir_gen_context.setInsertPoint(merge_block);
    llvm::PHINode *phi =
        builder->CreatePHI(builder->getInt1Ty(), 2, "logical_result");
    phi->addIncoming(is_and ? builder->getFalse() : builder->getTrue(),
                     short_circuit_block);
    phi->addIncoming(right_bool, right_exit_block);

    m_last_type = result_type;
    if (result_type->isDynamic()) {

      llvm::Type *dyn_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(result_type);
      llvm::Value *box_alloca =
          m_ir_gen_context.createAlloca(dyn_type, "short_circuit_dyn");
      llvm::Value *boxed = DynamicValueHandler::storePrimitiveToDynamic(
          phi, builder->getInt1Ty(), dyn_type, builder,
          analysis::Builtins::m_bool_type_instance.get());
      builder->CreateStore(boxed, box_alloca);
      m_last_value = box_alloca;
    } else {
      m_last_value = phi;
    }
    return;
  }

  // Non short-circuit: evaluate both operands
  binary_expression->getLeft()->accept(this);
  assert(m_last_value && "m_last_value is null");
  llvm::Value *left_value = m_last_value;
  types::Type *left_type = m_last_type;
  clearLast();
  binary_expression->getRight()->accept(this);
  assert(m_last_value && "m_last_value is null");
  llvm::Value *right_value = m_last_value;
  types::Type *right_type = m_last_type;
  clearLast();

  // For dynamic types, keep pointers; for primitives, resolve values
  if (!left_type->isDynamic()) {
    left_value = resolveValue(left_value, left_type);
  }
  if (!right_type->isDynamic()) {
    right_value = resolveValue(right_value, right_type);
  }

  auto binary_operator_result =
      getBinaryResult(left_value, right_value, binary_operator_kind,
                      binary_operator->getLeftType().get(),
                      binary_operator->getRightType().get(), result_type);
  m_last_type = result_type;
  m_last_value = binary_operator_result;
}
} // namespace flow_wing::ir_gen