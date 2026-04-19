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
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110 USA.
 */

#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundBreakStatement/BoundBreakStatement.hpp"

namespace flow_wing::ir_gen {

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundBreakStatement *statement) {
  llvm::BasicBlock *after_block =
      m_ir_gen_context.getCurrentLoopAfter();
  assert(after_block && "Break must be inside a loop (binding should enforce)");
  m_ir_gen_context.createBranch(after_block);
  llvm::BasicBlock *unreachable_block =
      m_ir_gen_context.createBlock("break.unreachable");
  m_ir_gen_context.setInsertPoint(unreachable_block);
  m_ir_gen_context.getLLVMBuilder()->CreateUnreachable();
  llvm::BasicBlock *next_block =
      m_ir_gen_context.createBlock("after.break");
  m_ir_gen_context.setInsertPoint(next_block);
}

} // namespace flow_wing::ir_gen
