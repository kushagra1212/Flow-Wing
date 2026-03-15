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
#include "src/SemanticAnalyzer/BoundStatements/BoundSwitchStatement/BoundSwitchStatement.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {

void IRGenerator::visit(binding::BoundSwitchStatement *statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Switch Statement", "IR GENERATION");

  auto *builder = m_ir_gen_context.getLLVMBuilder().get();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *current_function = m_ir_gen_context.getCurrentFunction();
  assert(current_function && "Switch statement must be inside a function");

  const auto &switch_condition = statement->getSwitchConditionExpression();
  const auto &default_case_statement = statement->getDefaultCaseStatement();
  const auto &case_expressions = statement->getCaseExpressions();
  const auto &case_statements = statement->getCaseStatements();

  switch_condition->accept(this);
  llvm::Value *cond_value = resolveValue(m_last_value, m_last_type);
  types::Type *cond_type = m_last_type;
  clearLast();

  auto *merge_block =
      llvm::BasicBlock::Create(*ctx, "switch.merge", current_function);

  llvm::BasicBlock *default_block = nullptr;
  if (default_case_statement) {
    default_block =
        llvm::BasicBlock::Create(*ctx, "switch.default", current_function);
  }

  llvm::BasicBlock *next_block =
      default_block ? default_block : merge_block;
  const size_t n = case_expressions.size();

  if (n == 0 && default_block) {
    builder->CreateBr(default_block);
  }

  for (size_t i = 0; i < n; ++i) {
    auto *case_body_block = llvm::BasicBlock::Create(
        *ctx, "switch.case." + std::to_string(i), current_function);

    if (i + 1 < n) {
      next_block = llvm::BasicBlock::Create(
          *ctx, "switch.check." + std::to_string(i + 1), current_function);
    } else {
      next_block = default_block ? default_block : merge_block;
    }

    case_expressions[i]->accept(this);
    llvm::Value *case_value = resolveValue(m_last_value, m_last_type);
    types::Type *case_type = m_last_type;
    clearLast();

    llvm::Value *eq_result = getEqualityComparisonBoolResult(
        cond_value, case_value, cond_type, case_type);

    builder->CreateCondBr(eq_result, case_body_block, next_block);

    m_ir_gen_context.setInsertPoint(case_body_block);
    case_statements[i]->accept(this);
    clearLast();
    if (builder->GetInsertBlock()->getTerminator() == nullptr) {
      m_ir_gen_context.createBranch(merge_block);
    }

    m_ir_gen_context.setInsertPoint(next_block);
  }

  if (default_case_statement) {
    m_ir_gen_context.setInsertPoint(default_block);
    default_case_statement->accept(this);
    clearLast();
    if (builder->GetInsertBlock()->getTerminator() == nullptr) {
      m_ir_gen_context.createBranch(merge_block);
    }
  }

  m_ir_gen_context.setInsertPoint(merge_block);
}

} // namespace flow_wing::ir_gen
