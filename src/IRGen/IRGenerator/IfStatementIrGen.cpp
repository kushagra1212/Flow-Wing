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
#include "src/SemanticAnalyzer/BoundStatements/BoundIfStatement/BoundIfStatement.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {

void IRGenerator::visit(binding::BoundIfStatement *statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound If Statement", "IR GENERATION");

  auto *builder = m_ir_gen_context.getLLVMBuilder().get();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *current_function = m_ir_gen_context.getCurrentFunction();
  assert(current_function && "If statement must be inside a function");

  auto *merge_block = llvm::BasicBlock::Create(*ctx, "if.merge", current_function);

  const auto &if_condition = statement->getIfCondition();
  const auto &if_statement = statement->getIfStatement();
  const auto &or_if_conditions = statement->getOrIfConditions();
  const auto &or_if_statements = statement->getOrIfStatements();
  const auto &else_clause = statement->getElseClause();

  auto *if_then_block =
      llvm::BasicBlock::Create(*ctx, "if.then", current_function);

  if (or_if_conditions.empty() && !else_clause) {
    if_condition->accept(this);
    llvm::Value *resolved = resolveValue(m_last_value, m_last_type);
    llvm::Value *cond_value = getConditionAsBool(resolved, m_last_type);
    clearLast();
    builder->CreateCondBr(cond_value, if_then_block, merge_block);

    m_ir_gen_context.setInsertPoint(if_then_block);
    if_statement->accept(this);
    clearLast();
    if (builder->GetInsertBlock()->getTerminator() == nullptr) {
      m_ir_gen_context.createBranch(merge_block);
    }
  } else {
    llvm::Value *resolved = nullptr;
    llvm::Value *cond_value = nullptr;
    llvm::BasicBlock *next_check_block = nullptr;
    if (!or_if_conditions.empty()) {
      next_check_block =
          llvm::BasicBlock::Create(*ctx, "if.or_if.check", current_function);
    } else if (else_clause) {
      next_check_block =
          llvm::BasicBlock::Create(*ctx, "if.else", current_function);
    } else {
      next_check_block = merge_block;
    }

    if_condition->accept(this);
    resolved = resolveValue(m_last_value, m_last_type);
    cond_value = getConditionAsBool(resolved, m_last_type);
    clearLast();
    builder->CreateCondBr(cond_value, if_then_block, next_check_block);

    m_ir_gen_context.setInsertPoint(if_then_block);
    if_statement->accept(this);
    clearLast();
    if (builder->GetInsertBlock()->getTerminator() == nullptr) {
      m_ir_gen_context.createBranch(merge_block);
    }

    for (size_t i = 0; i < or_if_conditions.size(); ++i) {
      auto *or_if_then_block = llvm::BasicBlock::Create(
          *ctx, "if.or_if.then." + std::to_string(i), current_function);

      llvm::BasicBlock *or_if_next = nullptr;
      if (i + 1 < or_if_conditions.size()) {
        or_if_next = llvm::BasicBlock::Create(
            *ctx, "if.or_if.check." + std::to_string(i + 1), current_function);
      } else if (else_clause) {
        or_if_next =
            llvm::BasicBlock::Create(*ctx, "if.else", current_function);
      } else {
        or_if_next = merge_block;
      }

      m_ir_gen_context.setInsertPoint(next_check_block);
      or_if_conditions[i]->accept(this);
      resolved = resolveValue(m_last_value, m_last_type);
      cond_value = getConditionAsBool(resolved, m_last_type);
      clearLast();
      builder->CreateCondBr(cond_value, or_if_then_block, or_if_next);

      m_ir_gen_context.setInsertPoint(or_if_then_block);
      or_if_statements[i]->accept(this);
      clearLast();
      if (builder->GetInsertBlock()->getTerminator() == nullptr) {
        m_ir_gen_context.createBranch(merge_block);
      }

      next_check_block = or_if_next;
    }

    if (else_clause) {
      m_ir_gen_context.setInsertPoint(next_check_block);
      else_clause->accept(this);
      clearLast();
      if (builder->GetInsertBlock()->getTerminator() == nullptr) {
        m_ir_gen_context.createBranch(merge_block);
      }
    }
  }

  m_ir_gen_context.setInsertPoint(merge_block);
}

} // namespace flow_wing::ir_gen
