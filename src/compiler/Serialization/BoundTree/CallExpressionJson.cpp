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

#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {

void BoundTreeJson::visit(binding::BoundCallExpression *call_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Call Expression", "BOUND TREE");
  nlohmann::json call_expression_json;
  call_expression_json["kind"] = toString(call_expression->getKind());

  call_expression_json["symbol_id"] = getSymbolId(call_expression->getSymbol());

  serializeArray(call_expression->getArguments(), call_expression_json,
                 "arguments");

  call_expression_json["range"] =
      toJsonRange(call_expression->getSourceLocation());
  m_last_node_json = std::move(call_expression_json);
}
} // namespace flow_wing::compiler::serializer