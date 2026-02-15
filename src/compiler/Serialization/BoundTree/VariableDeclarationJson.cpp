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

#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {
void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundVariableDeclaration *variable_declaration) {
  PARSER_DEBUG_LOG("Visiting Bound Variable Declaration", "BOUND TREE");

  nlohmann::json variable_declaration_json;
  variable_declaration_json["kind"] = toString(variable_declaration->getKind());

  for (const auto &symbol : variable_declaration->getSymbols()) {
    const auto &variable_symbol =
        static_cast<const analysis::VariableSymbol *>(symbol.get());
    const auto &symbol_id = getSymbolId(variable_symbol);

    if (variable_symbol->getInitializerExpression()) {

      variable_symbol->getInitializerExpression()->accept(this);
    }

    m_last_node_json["symbol_id"] = symbol_id;
    variable_declaration_json["initializer_expressions"].push_back(
        std::move(m_last_node_json));
  }

  variable_declaration_json["range"] =
      toJsonRange(variable_declaration->getSourceLocation());

  m_last_node_json = std::move(variable_declaration_json);
}
} // namespace flow_wing::compiler::serializer