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
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {
void IRGenerator::visit(
    binding::BoundIdentifierExpression *identifier_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Identifier Expression", "IR GENERATION");

  auto symbol = identifier_expression->getSymbol();
  auto llvm_value = m_ir_gen_context.getSymbol(symbol->getName());
  assert(llvm_value && "Symbol not found [BoundIdentifierExpression::visit]");

  m_last_type = symbol->getType().get();
  m_last_value = llvm_value;
}

}; // namespace flow_wing::ir_gen