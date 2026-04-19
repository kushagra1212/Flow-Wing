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



#include "src/SemanticAnalyzer/BoundExpressions/BoundMemberAccessExpression/BoundMemberAccessExpression.hpp"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"
namespace flow_wing::compiler::serializer {
void BoundTreeJson::visit(
    binding::BoundMemberAccessExpression *member_access_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Member Access Expression", "BOUND TREE");
  nlohmann::json member_access_expression_json;
  member_access_expression_json["kind"] =
      toString(member_access_expression->getKind());
  serializeChild(member_access_expression->getLeftExpression(),
                 member_access_expression_json, "left_expression");
  member_access_expression_json["member_name"] =
      member_access_expression->getMemberName();
  member_access_expression_json["field_type_id"] =
      getTypeId(member_access_expression->getType().get());
  member_access_expression_json["range"] =
      toJsonRange(member_access_expression->getSourceLocation());
  m_last_node_json = std::move(member_access_expression_json);
}
} // namespace flow_wing::compiler::serializer