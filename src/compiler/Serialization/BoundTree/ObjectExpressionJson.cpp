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

#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundObjectExpression *object_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Object Expression", "BOUND TREE");
  nlohmann::json object_expression_json;
  object_expression_json["kind"] = toString(object_expression->getKind());
  size_t total_members = object_expression->getColonExpressions().size();
  for (size_t member_index = 0; member_index < total_members; ++member_index) {
    nlohmann::json member_json;

    object_expression->getColonExpressions()[member_index]->accept(this);
    member_json["expression"] = m_last_node_json;

    object_expression_json["members"].push_back(std::move(member_json));
  }
  object_expression_json["type"] =
      getTypeId(object_expression->getType().get());
  object_expression_json["range"] =
      toJsonRange(object_expression->getSourceLocation());
  m_last_node_json = std::move(object_expression_json);
}
} // namespace flow_wing::compiler::serializer