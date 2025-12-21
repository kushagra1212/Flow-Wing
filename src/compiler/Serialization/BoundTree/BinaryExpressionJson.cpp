/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {
nlohmann::json BoundTreeJson::getBinaryOperatorJson(
    const binding::BoundBinaryOperator *binary_operator) {
  PARSER_DEBUG_LOG("Visiting Bound Binary Operator", "BOUND TREE");
  nlohmann::json binary_operator_json;
  binary_operator_json["kind"] = toString(binary_operator->getSyntaxKind());
  binary_operator_json["leftTypeId"] =
      getTypeId(binary_operator->getLeftType().get());
  binary_operator_json["rightTypeId"] =
      getTypeId(binary_operator->getRightType().get());
  binary_operator_json["resultTypeId"] =
      getTypeId(binary_operator->getResultType().get());

  return binary_operator_json;
}

void BoundTreeJson::visit(binding::BoundBinaryExpression *binary_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Binary Expression", "BOUND TREE");
  nlohmann::json binary_expression_json;
  binary_expression_json["kind"] = toString(binary_expression->getKind());
  serializeChild(binary_expression->getLeft(), binary_expression_json,
                 "leftExpression");

  binary_expression_json["binaryOperator"] =
      getBinaryOperatorJson(binary_expression->getBinaryOperator().get());

  serializeChild(binary_expression->getRight(), binary_expression_json,
                 "rightExpression");

  binary_expression_json["range"] =
      toJsonRange(binary_expression->getSourceLocation());

  m_last_node_json = std::move(binary_expression_json);
}
} // namespace flow_wing::compiler::serializer