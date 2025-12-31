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
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundAssignmentExpression *statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Assignment Expression", "IR GENERATION");

  size_t size = statement->getLeft().size();

  for (size_t i = 0; i < size; i++) {
    auto &left_expressions = statement->getLeft();
    auto &right_expressions = statement->getRight();

    size_t left_size = left_expressions.size();

    for (size_t j = 0; j < left_size; j++) {
      auto &left_expression = left_expressions.at(j);
      auto &right_expression = right_expressions.at(j);

      left_expression->accept(this);
      auto left_pointer = m_last_value;
      auto left_type = m_last_type;

      assert(left_pointer && "left_pointer is null");
      assert(left_type && "left_type is null");
      clearLast();

      right_expression->accept(this);
      auto right_value = resolveValue(m_last_value, m_last_type);
      auto right_type = m_last_type;

      assert(right_value && "right_value is null");
      assert(right_type && "right_type is null");
      clearLast();

      if (left_type != right_type) {
        right_value = convertToTargetType(right_value, left_type, right_type);
      }
      m_ir_gen_context.getLLVMBuilder()->CreateStore(right_value, left_pointer);
    }
  }
}
}; // namespace flow_wing::ir_gen