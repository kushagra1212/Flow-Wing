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

#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.hpp"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {

void BoundTreeJson::visit(binding::BoundUnaryExpression *unary_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Unary Expression", "BOUND TREE");
  nlohmann::json unary_expression_json;
  unary_expression_json["kind"] = toString(unary_expression->getKind());
  auto operator_token_kind = toString(unary_expression->getOperatorTokenKind());
  auto result_type_id = getTypeId(unary_expression->getType().get());
  auto expression_type_id =
      getTypeId(unary_expression->getExpression()->getType().get());

  unary_expression_json["unary_operator"] = {
      {"kind", operator_token_kind},
      {"type_id", expression_type_id},
      {"result_type_id", result_type_id},
  };

  serializeChild(unary_expression->getExpression(), unary_expression_json,
                 "expression");
  unary_expression_json["range"] =
      toJsonRange(unary_expression->getSourceLocation());
  m_last_node_json = std::move(unary_expression_json);
}
} // namespace flow_wing::compiler::serializer