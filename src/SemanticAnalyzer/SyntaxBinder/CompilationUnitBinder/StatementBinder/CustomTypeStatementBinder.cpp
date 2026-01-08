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

#include "StatementBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/TypeResolver/TypeResolver.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/utils/LogConfig.h"
#include <cassert>
#include <map>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement> StatementBinder::bindCustomTypeStatement(
    syntax::CustomTypeStatementSyntax *statement) {
  assert(statement != nullptr &&
         "CustomTypeExpressionBinder::bind: expression is null");

  auto identifier_expression =
      static_cast<syntax::IdentifierExpressionSyntax *>(
          statement->getTypeName().get());

  const auto &custom_type_name = identifier_expression->getValue();

  auto custom_type_type = std::make_shared<types::CustomObjectType>(
      custom_type_name, std::map<std::string, std::shared_ptr<types::Type>>{});
  auto symbol_table = m_context->getSymbolTable().get();

  // --- STEP 2: Register it IMMEDIATELY ---
  // This allows the inner fields to find "Node" while we are still binding
  // them.
  auto symbol = std::make_shared<analysis::Symbol>(
      custom_type_name, analysis::SymbolKind::kObject, custom_type_type);

  if (!symbol_table->define(symbol)) {
    auto error_statement = std::make_unique<BoundErrorStatement>(
        statement->getSourceLocation(),
        diagnostic::DiagnosticCode::kCustomTypeAlreadyDeclared,
        diagnostic::DiagnosticArgs{custom_type_name});

    m_context->reportError(error_statement.get());
    return std::move(error_statement);
  }

  std::map<std::string, std::shared_ptr<types::Type>>
      custom_type_field_types_map;

  for (const auto &field_declaration : statement->getFieldDeclarations()) {
    auto field_name = static_cast<syntax::IdentifierExpressionSyntax *>(
        field_declaration->getKey().get());
    const auto &field_name_value = field_name->getValue();

    auto result = m_context->getTypeResolver()->resolveType(
        field_declaration->getValue().get());

    if (result.second != nullptr) {
      m_context->reportError(result.second.get());
      return std::make_unique<BoundErrorStatement>(std::move(result.second));
    }
    custom_type_field_types_map.insert({field_name_value, result.first});
  }

  custom_type_type->setFieldTypesMap(std::move(custom_type_field_types_map));

  return std::make_unique<BoundCustomTypeStatement>(
      std::vector<std::shared_ptr<analysis::Symbol>>({symbol}),
      statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing
