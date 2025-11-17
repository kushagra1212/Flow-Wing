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


#include "StatementBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/TypeResolver/TypeResolver.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement> StatementBinder::bindVariableDeclaration(
    syntax::VariableDeclarationSyntax *statement) {
  auto node = static_cast<syntax::VariableDeclarationSyntax *>(statement);

  auto has_const_keyword = node->hasConstKeyword();
  auto symbol_table = m_context->getSymbolTable().get();

  std::vector<std::shared_ptr<analysis::Symbol>> variable_symbols;

  for (const auto &declarator : node->getDeclarators()) {

    auto identifier_expression =
        static_cast<syntax::IdentifierExpressionSyntax *>(
            declarator->getIdentifierExpression().get());

    const auto &type = m_context->getTypeResolver()->resolveType(
        declarator->getTypeExpression().get());

    if (type == nullptr) {
      return std::make_unique<BoundErrorStatement>(
          declarator->getTypeExpression()->getSourceLocation());
    }

    auto variable_symbol = std::make_shared<analysis::VariableSymbol>(
        identifier_expression->getValue(), type, has_const_keyword);

    if (!symbol_table->define(variable_symbol)) {
      m_context->reportError(
          diagnostic::DiagnosticCode::kVariableAlreadyDeclared,
          {identifier_expression->getValue()},
          identifier_expression->getSourceLocation());

      return std::make_unique<BoundErrorStatement>(
          identifier_expression->getSourceLocation());
    }

    variable_symbols.push_back(variable_symbol);
  }

  auto initializer_expression = node->getInitializerExpression().get();
  std::vector<std::unique_ptr<binding::BoundExpression>>
      bound_initializer_expressions = {};

  if (initializer_expression) {
    bound_initializer_expressions =
        m_expression_binder->bindExpressionList(initializer_expression);

    if (bound_initializer_expressions.size() > variable_symbols.size()) {
      m_context->reportError(
          diagnostic::DiagnosticCode::kTooManyInitializerExpressions,
          {std::to_string(variable_symbols.size()),
           std::to_string(bound_initializer_expressions.size())},
          initializer_expression->getSourceLocation());

      return std::make_unique<BoundErrorStatement>(
          initializer_expression->getSourceLocation());
    }
    const size_t size = bound_initializer_expressions.size();

    for (size_t i = 0; i < size; i++) {
      if (bound_initializer_expressions[i]->getKind() ==
          NodeKind::kErrorExpression) {
        return std::make_unique<BoundErrorStatement>(
            initializer_expression->getSourceLocation());
      }

      const auto &expression_type = bound_initializer_expressions[i]->getType();

      const auto &variable_type = variable_symbols[i]->getType();

      if (expression_type != variable_type && !variable_type->isDynamic() &&
          !expression_type->isDynamic()) {
        m_context->reportError(
            diagnostic::DiagnosticCode::kInitializerExpressionTypeMismatch,
            {variable_type->getName(), expression_type->getName()},
            initializer_expression->getSourceLocation());

        return std::make_unique<BoundErrorStatement>(
            initializer_expression->getSourceLocation());
      }

      static_cast<analysis::VariableSymbol *>(variable_symbols[i].get())
          ->setInitializerExpression(
              std::move(bound_initializer_expressions[i]));
    }
  }

  return std::make_unique<BoundVariableDeclaration>(variable_symbols,
                                                    node->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing