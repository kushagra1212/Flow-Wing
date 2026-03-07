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



#include "src/SemanticAnalyzer/DeclarationAnalyzer/DeclarationAnalyzer.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"

namespace flow_wing {
void analysis::DeclarationAnalyzer::visit(
    syntax::CustomTypeStatementSyntax *node) {
  auto identifier = static_cast<syntax::IdentifierExpressionSyntax *>(
      node->getTypeName().get());
  const auto &type_name = identifier->getValue();

  auto custom_type = std::make_shared<types::CustomObjectType>(
      type_name, std::map<std::string, std::shared_ptr<types::Type>>{}, true);

  auto symbol = std::make_shared<analysis::Symbol>(
      type_name, analysis::SymbolKind::kObject, custom_type);

  m_binder_context.getSymbolTable()->define(symbol);
}
} // namespace flow_wing