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
#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/Type.hpp"
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
      auto *target_ptr = m_last_value;
      auto *target_type = m_last_type;

      assert(target_ptr && "target pointer is null");
      assert(target_type && "target type is null");
      clearLast();

      right_expression->accept(this);
      auto *source_val = m_last_value;
      auto *source_type = m_last_type;

      assert(source_val && "Assignment source value is null");

      CODEGEN_DEBUG_LOG("Target Type", target_type->getName());
      CODEGEN_DEBUG_LOG("Source Type", source_type->getName());

      emitTypedStore(target_ptr, target_type, source_val, source_type);

      clearLast();
    }
  }
}
}; // namespace flow_wing::ir_gen