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

#include "src/SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundCustomTypeStatement *custom_type_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Custom Type Statement", "BOUND TREE");
  nlohmann::json custom_type_statement_json;
  custom_type_statement_json["kind"] =
      toString(custom_type_statement->getKind());

  for (const auto &symbol : custom_type_statement->getSymbols()) {
    nlohmann::json symbol_json;
    DEBUG_LOG("Symbol: %s", symbol->toString(symbol->getKind()).c_str());
    custom_type_statement_json["symbolIds"].push_back(
        getSymbolId(symbol.get()));
  }

  custom_type_statement_json["range"] =
      toJsonRange(custom_type_statement->getSourceLocation());
  m_last_node_json = std::move(custom_type_statement_json);
}
} // namespace flow_wing::compiler::serializer