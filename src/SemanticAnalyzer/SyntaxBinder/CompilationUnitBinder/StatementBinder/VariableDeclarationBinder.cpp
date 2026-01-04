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
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/TypeResolver/TypeResolver.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "src/utils/LogConfig.h"
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

    std::pair<std::shared_ptr<types::Type>,
              std::unique_ptr<binding::BoundErrorExpression>>
        result = m_context->getTypeResolver()->resolveType(
            declarator->getTypeExpression().get());

    if (result.second != nullptr) {
      m_context->reportError(result.second.get());
      return std::make_unique<BoundErrorStatement>(std::move(result.second));
    }

    auto type = result.first;

    auto variable_symbol = std::make_shared<analysis::VariableSymbol>(
        identifier_expression->getValue(), type, has_const_keyword);

    if (!symbol_table->define(variable_symbol)) {

      auto error_statement = std::make_unique<BoundErrorStatement>(
          identifier_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kVariableAlreadyDeclared,
          diagnostic::DiagnosticArgs{identifier_expression->getValue()});
      m_context->reportError(error_statement.get());
      return std::move(error_statement);
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

      auto error_statement = std::make_unique<BoundErrorStatement>(
          initializer_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kTooManyInitializerExpressions,
          diagnostic::DiagnosticArgs{
              std::to_string(variable_symbols.size()),
              std::to_string(bound_initializer_expressions.size())});
      m_context->reportError(error_statement.get());
      return std::move(error_statement);
    }
    const size_t size = bound_initializer_expressions.size();

    for (size_t i = 0; i < size; i++) {
      if (bound_initializer_expressions[i]->getKind() ==
          NodeKind::kErrorExpression) {
        return std::make_unique<BoundErrorStatement>(
            std::move(bound_initializer_expressions[i]));
      }

      const auto &expression_type = bound_initializer_expressions[i]->getType();

      auto variable_type = variable_symbols[i]->getType();

      // auto *raw_expr = bound_initializer_expressions[i].get();
      // if (raw_expr->getKind() == NodeKind::kObjectExpression) {

      //   auto *obj_expr = static_cast<BoundObjectExpression *>(raw_expr);

      //   // Force the Object Expression to adopt the Variable's Type
      //   obj_expr->setType(variable_type);
      // }

      BINDER_DEBUG_LOG("Expression Type: ", expression_type->getName());
      BINDER_DEBUG_LOG("Expression is Dynamic: ", expression_type->isDynamic());
      BINDER_DEBUG_LOG("Variable Type: ", variable_type->getName());
      BINDER_DEBUG_LOG("Variable is Dynamic: ", variable_type->isDynamic());

      if (variable_type->isDynamic()) {
        // Variable is dynamic: expression must be dynamic or primitive
        if (!expression_type->isDynamic() && !expression_type->isPrimitive()) {
          auto error_expression = std::make_unique<BoundErrorExpression>(
              bound_initializer_expressions[i]->getSourceLocation(),
              diagnostic::DiagnosticCode::kInitializerExpressionTypeMismatch,
              diagnostic::DiagnosticArgs{variable_type->getName(),
                                         expression_type->getName(),
                                         variable_symbols[i]->getName()});
          m_context->reportError(error_expression.get());
          static_cast<analysis::VariableSymbol *>(variable_symbols[i].get())
              ->setInitializerExpression(std::move(error_expression));
        } else {
          // Dynamic can hold any primitive or dynamic
          static_cast<analysis::VariableSymbol *>(variable_symbols[i].get())
              ->setInitializerExpression(
                  std::move(bound_initializer_expressions[i]));
        }
      } else if (expression_type->isDynamic()) {
        // Expression is dynamic: variable can hold it (will be extracted at
        // runtime)
        static_cast<analysis::VariableSymbol *>(variable_symbols[i].get())
            ->setInitializerExpression(
                std::move(bound_initializer_expressions[i]));
      } else if (*expression_type > *variable_type) {
        auto error_expression = std::make_unique<BoundErrorExpression>(
            bound_initializer_expressions[i]->getSourceLocation(),
            diagnostic::DiagnosticCode::kInitializerExpressionTypeMismatch,
            diagnostic::DiagnosticArgs{variable_type->getName(),
                                       expression_type->getName(),
                                       variable_symbols[i]->getName()});

        m_context->reportError(error_expression.get());

        static_cast<analysis::VariableSymbol *>(variable_symbols[i].get())
            ->setInitializerExpression(std::move(error_expression));
      } else {
        static_cast<analysis::VariableSymbol *>(variable_symbols[i].get())
            ->setInitializerExpression(
                std::move(bound_initializer_expressions[i]));
      }
    }
  }

  return std::make_unique<BoundVariableDeclaration>(variable_symbols,
                                                    node->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing