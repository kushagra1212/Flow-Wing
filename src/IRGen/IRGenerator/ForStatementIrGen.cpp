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
#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundForStatement/BoundForStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/utils/LogConfig.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"

namespace flow_wing::ir_gen {

void IRGenerator::visit(binding::BoundForStatement *statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound For Statement", "IR GENERATION");

  auto *builder = m_ir_gen_context.getLLVMBuilder().get();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *current_function = m_ir_gen_context.getCurrentFunction();
  assert(current_function && "For statement must be inside a function");

  std::string var_name;
  types::Type *var_type = nullptr;

  if (statement->getVariableDeclaration() != nullptr) {
    auto *var_decl = static_cast<binding::BoundVariableDeclaration *>(
        statement->getVariableDeclaration().get());
    auto &symbols = var_decl->getSymbols();
    assert(!symbols.empty() &&
           "For loop variable declaration must have one symbol");
    var_name = symbols[0]->getName();
    var_type = symbols[0]->getType().get();
  } else {
    auto *assign = static_cast<binding::BoundAssignmentExpression *>(
        statement->getAssignmentExpression().get());
    auto &left = assign->getLeft();
    assert(!left.empty() &&
           left[0]->getKind() == binding::NodeKind::kIdentifierExpression);
    auto *ident =
        static_cast<binding::BoundIdentifierExpression *>(left[0].get());
    var_name = ident->getSymbol()->getName();
    var_type = assign->getType().get();
  }
  assert(var_type && "For loop variable type must be set");

  auto *cond_block =
      llvm::BasicBlock::Create(*ctx, "for.cond", current_function);
  auto *body_block =
      llvm::BasicBlock::Create(*ctx, "for.body", current_function);
  auto *increment_block =
      llvm::BasicBlock::Create(*ctx, "for.increment", current_function);
  auto *after_block =
      llvm::BasicBlock::Create(*ctx, "for.after", current_function);

  if (statement->getVariableDeclaration() != nullptr) {
    statement->getVariableDeclaration()->accept(this);
  } else {
    statement->getAssignmentExpression()->accept(this);
  }
  clearLast();
  m_ir_gen_context.createBranch(cond_block);

  m_ir_gen_context.setInsertPoint(cond_block);
  llvm::Value *var_ptr = m_ir_gen_context.getSymbol(var_name);
  assert(var_ptr && "For loop variable must be in symbol table");
  llvm::Value *var_val = resolveValue(var_ptr, var_type);

  statement->getUpperBound()->accept(this);
  llvm::Value *bound_val = resolveValue(m_last_value, m_last_type);
  types::Type *bound_type = m_last_type;
  clearLast();

  statement->getStep()->accept(this);
  llvm::Value *step_val = resolveValue(m_last_value, m_last_type);
  types::Type *step_type = m_last_type;
  clearLast();

  // Promote int8 to int32 for condition/increment to avoid int8 comparison
  // paths that can trigger wrong runtime conversion (e.g. string_to_int).
  types::Type *cond_var_type = var_type;
  types::Type *cond_bound_type = bound_type;
  types::Type *cond_step_type = step_type;
  llvm::Value *cond_var_val = var_val;
  llvm::Value *cond_bound_val = bound_val;
  llvm::Value *cond_step_val = step_val;
  bool promote_i8 = (var_val->getType()->isIntegerTy(8));
  if (promote_i8) {
    cond_var_type = analysis::Builtins::m_int32_type_instance.get();
    cond_bound_type = analysis::Builtins::m_int32_type_instance.get();
    cond_step_type = analysis::Builtins::m_int32_type_instance.get();
    cond_var_val = convertToInt32(var_val, var_val->getType());
    cond_bound_val = convertToInt32(bound_val, bound_val->getType());
    cond_step_val = convertToInt32(step_val, step_val->getType());
  }

  llvm::Value *step_positive = nullptr;
  if (cond_step_type->isDynamic()) {
    llvm::Value *zero_dyn = m_ir_gen_context.getDefaultValue(step_type, false);
    step_positive =
        getBooleanResult(step_val, zero_dyn, lexer::TokenKind::kGreaterToken,
                         step_type, step_type);
  } else {
    llvm::Type *step_llvm_ty =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(cond_step_type);
    llvm::Value *zero = llvm::ConstantInt::get(step_llvm_ty, 0);
    step_positive = getGreaterThanBoolResult(cond_step_val, zero,
                                             cond_step_type, cond_step_type);
  }

  llvm::Value *cond_positive = getLessThanOrEqualBoolResult(
      cond_var_val, cond_bound_val, cond_var_type, cond_bound_type);
  llvm::Value *cond_negative = getGreaterThanOrEqualBoolResult(
      cond_var_val, cond_bound_val, cond_var_type, cond_bound_type);
  llvm::Value *and_pos =
      getLogicalAndBoolResult(step_positive, cond_positive,
                              analysis::Builtins::m_bool_type_instance.get(),
                              analysis::Builtins::m_bool_type_instance.get());
  llvm::Value *not_step_pos =
      builder->CreateNot(step_positive, "step_not_positive");
  llvm::Value *and_neg =
      getLogicalAndBoolResult(not_step_pos, cond_negative,
                              analysis::Builtins::m_bool_type_instance.get(),
                              analysis::Builtins::m_bool_type_instance.get());
  llvm::Value *should_continue = getLogicalOrBoolResult(
      and_pos, and_neg, analysis::Builtins::m_bool_type_instance.get(),
      analysis::Builtins::m_bool_type_instance.get());
  builder->CreateCondBr(should_continue, body_block, after_block);

  m_ir_gen_context.setInsertPoint(body_block);
  m_ir_gen_context.pushLoop(increment_block, after_block);
  statement->getBody()->accept(this);
  clearLast();
  m_ir_gen_context.popLoop();
  if (builder->GetInsertBlock()->getTerminator() == nullptr) {
    m_ir_gen_context.createBranch(increment_block);
  }

  m_ir_gen_context.setInsertPoint(increment_block);
  var_val = resolveValue(var_ptr, var_type);
  statement->getStep()->accept(this);
  llvm::Value *step_val_inc = resolveValue(m_last_value, m_last_type);
  clearLast();
  llvm::Value *new_val;
  if (promote_i8) {
    llvm::Value *var_i32 = convertToInt32(var_val, var_val->getType());
    llvm::Value *step_i32 =
        convertToInt32(step_val_inc, step_val_inc->getType());
    llvm::Value *sum_i32 =
        getBinaryResult(var_i32, step_i32, lexer::TokenKind::kPlusToken,
                        cond_var_type, cond_step_type, cond_var_type);
    new_val = convertToInt8(sum_i32, sum_i32->getType());
  } else {
    new_val =
        getBinaryResult(var_val, step_val_inc, lexer::TokenKind::kPlusToken,
                        var_type, step_type, var_type);
  }
  emitTypedStore(var_ptr, var_type, new_val, var_type);
  m_ir_gen_context.createBranch(cond_block);

  m_ir_gen_context.setInsertPoint(after_block);
}

} // namespace flow_wing::ir_gen
