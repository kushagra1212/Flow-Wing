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

#include "src/SemanticAnalyzer/BoundStatements/BoundFunctionStatement/BoundFunctionStatement.hpp"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"
namespace flow_wing::compiler::serializer {
void BoundTreeJson::visit(binding::BoundFunctionStatement *function_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Function Statement", "BOUND TREE");

  nlohmann::json function_statement_json;
  function_statement_json["kind"] = toString(function_statement->getKind());

  assert(function_statement->getSymbols().size() == 1 &&
         "Function statement must have at least one symbol");

  auto function_symbol = static_cast<analysis::FunctionSymbol *>(
      function_statement->getSymbols()[0].get());

  function_statement_json["symbol_id"] = getSymbolId(function_symbol);

  if (function_symbol->getBody() != nullptr) {
    serializeChild(function_symbol->getBody(), function_statement_json, "body");
  }

  for (const auto &parameter : function_symbol->getParameters()) {
    nlohmann::json parameter_json;
    parameter_json["parameter_symbol_id"] = getShortId(parameter.get());
    if (parameter->getDefaultValueExpression() != nullptr) {
      serializeChild(parameter->getDefaultValueExpression(), parameter_json,
                     "default_value_expression");
    }
    function_statement_json["parameters"].push_back(std::move(parameter_json));
  }
  auto function_type = static_cast<const types::FunctionType *>(
      function_symbol->getType().get());

  for (const auto &return_type : function_type->getReturnTypes()) {

    function_statement_json["return_type_ids"].push_back(
        getTypeId(return_type.get()));
  }

  function_statement_json["range"] =
      toJsonRange(function_statement->getSourceLocation());
  m_last_node_json = std::move(function_statement_json);
}
}; // namespace flow_wing::compiler::serializer