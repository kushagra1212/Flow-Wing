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

#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {
void BoundTreeJson::visit([[maybe_unused]] binding::BoundAssignmentExpression
                              *assignment_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Assignment Expression", "BOUND TREE");

  nlohmann::json assignment_expression_json;

  assignment_expression_json["kind"] =
      toString(assignment_expression->getKind());

  serializeArray(assignment_expression->getLeft(), assignment_expression_json,
                 "left");

  serializeArray(assignment_expression->getRight(), assignment_expression_json,
                 "right");

  assignment_expression_json["range"] =
      toJsonRange(assignment_expression->getSourceLocation());

  assignment_expression_json["is_full_re_assignment"] =
      assignment_expression->isFullReAssignment();

  assignment_expression_json["is_multi_target_assignment"] =
      assignment_expression->isMultiTargetAssignment();

  m_last_node_json = std::move(assignment_expression_json);
}
} // namespace flow_wing::compiler::serializer