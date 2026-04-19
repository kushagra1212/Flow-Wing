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
#include "src/SemanticAnalyzer/BoundStatements/BoundWhileStatement/BoundWhileStatement.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {

void IRGenerator::visit(binding::BoundWhileStatement *statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound While Statement", "IR GENERATION");

  auto *builder = m_ir_gen_context.getLLVMBuilder().get();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *current_function = m_ir_gen_context.getCurrentFunction();
  assert(current_function && "While statement must be inside a function");

  auto *cond_block =
      llvm::BasicBlock::Create(*ctx, "while.cond", current_function);
  auto *body_block =
      llvm::BasicBlock::Create(*ctx, "while.body", current_function);
  auto *after_block =
      llvm::BasicBlock::Create(*ctx, "while.after", current_function);

  m_ir_gen_context.createBranch(cond_block);
  m_ir_gen_context.setInsertPoint(cond_block);

  statement->getCondition()->accept(this);
  llvm::Value *resolved = resolveValue(m_last_value, m_last_type);
  llvm::Value *cond_value = getConditionAsBool(resolved, m_last_type);
  clearLast();
  builder->CreateCondBr(cond_value, body_block, after_block);

  m_ir_gen_context.setInsertPoint(body_block);
  m_ir_gen_context.pushLoop(cond_block, after_block);
  statement->getStatement()->accept(this);
  clearLast();
  m_ir_gen_context.popLoop();
  if (builder->GetInsertBlock()->getTerminator() == nullptr) {
    m_ir_gen_context.createBranch(cond_block);
  }

  m_ir_gen_context.setInsertPoint(after_block);
}

} // namespace flow_wing::ir_gen
