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
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTernaryExpression/BoundTernaryExpression.h"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
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

    variable_symbol->setDeclarationSite(
        m_context->getCompilationContext().getAbsoluteSourceFilePath(),
        identifier_expression->getSourceLocation());

    variable_symbols.push_back(variable_symbol);
  }

  auto initializer_expression = node->getInitializerExpression().get();
  std::vector<std::unique_ptr<binding::BoundExpression>>
      bound_initializer_expressions = {};

  if (initializer_expression) {
    bound_initializer_expressions =
        m_expression_binder->bindExpressionList(initializer_expression);

    // Calculate the "flattened" count of provided initializer values
    size_t total_initializer_count = 0;
    for (const auto &expr : bound_initializer_expressions) {
      if (expr->isMultipleType()) {
        total_initializer_count += expr->getMultipleTypes().size();
      } else {
        total_initializer_count += 1;
      }
    }

    if (total_initializer_count > variable_symbols.size()) {
      auto error_statement = std::make_unique<BoundErrorStatement>(
          initializer_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kTooManyInitializerExpressions,
          diagnostic::DiagnosticArgs{std::to_string(variable_symbols.size()),
                                     std::to_string(total_initializer_count)});
      m_context->reportError(error_statement.get());
      return std::move(error_statement);
    }

    if (node->hasConstKeyword()) {
      if (total_initializer_count == 0) {
        auto error_statement = std::make_unique<BoundErrorStatement>(
            node->getSourceLocation(),
            diagnostic::DiagnosticCode::kMissingInitializerExpression,
            diagnostic::DiagnosticArgs{variable_symbols[0]->getName()});
        m_context->reportError(error_statement.get());
        return std::move(error_statement);
      }

      if (total_initializer_count < variable_symbols.size()) {
        auto error_statement = std::make_unique<BoundErrorStatement>(
            node->getSourceLocation(),
            diagnostic::DiagnosticCode::kTooFewInitializerExpressions,
            diagnostic::DiagnosticArgs{
                std::to_string(variable_symbols.size()),
                std::to_string(total_initializer_count)});
        m_context->reportError(error_statement.get());
        return std::move(error_statement);
      }
    }

    size_t var_idx = 0;
    for (auto &expr : bound_initializer_expressions) {
      if (expr && expr->getKind() == NodeKind::kErrorExpression) {
        return std::make_unique<BoundErrorStatement>(std::move(expr));
      }

      std::vector<std::shared_ptr<types::Type>> expr_types;
      bool is_multi = expr->isMultipleType();

      if (is_multi) {
        expr_types = expr->getMultipleTypes();
      } else {
        expr_types.push_back(expr->getType());
      }

      for (const auto &expression_type : expr_types) {
        if (var_idx >= variable_symbols.size())
          break;

        auto variable_type = variable_symbols[var_idx]->getType();

        if (expression_type->isNthg()) {
          auto error_expression = std::make_unique<BoundErrorExpression>(
              expr->getSourceLocation(),
              diagnostic::DiagnosticCode::kInitializerExpressionTypeMismatch,
              diagnostic::DiagnosticArgs{
                  variable_type->getName(), expression_type->getName(),
                  variable_symbols[var_idx]->getName()});
          m_context->reportError(error_expression.get());
          static_cast<analysis::VariableSymbol *>(
              variable_symbols[var_idx].get())
              ->setInitializerExpression(std::move(error_expression));
          if (!is_multi)
            expr = nullptr;
          var_idx++;
          continue;
        }

        BINDER_DEBUG_LOG("Expression Type: ", expression_type->getName());
        BINDER_DEBUG_LOG("Expression is Dynamic: ",
                         expression_type->isDynamic());
        BINDER_DEBUG_LOG("Variable Type: ", variable_type->getName());
        BINDER_DEBUG_LOG("Variable is Dynamic: ", variable_type->isDynamic());

        if (variable_type->isDynamic()) {
          if (!expression_type->isDynamic() &&
              !expression_type->isPrimitive()) {
            auto error_expression = std::make_unique<BoundErrorExpression>(
                expr->getSourceLocation(),
                diagnostic::DiagnosticCode::kInitializerExpressionTypeMismatch,
                diagnostic::DiagnosticArgs{
                    variable_type->getName(), expression_type->getName(),
                    variable_symbols[var_idx]->getName()});
            m_context->reportError(error_expression.get());
            static_cast<analysis::VariableSymbol *>(
                variable_symbols[var_idx].get())
                ->setInitializerExpression(std::move(error_expression));
            if (!is_multi)
              expr = nullptr;
          } else if (!is_multi) {
            static_cast<analysis::VariableSymbol *>(
                variable_symbols[var_idx].get())
                ->setInitializerExpression(std::move(expr));
          }
        } else if (expression_type->isDynamic()) {
          if (!variable_type->isDynamic() && expr &&
              expr->getKind() == NodeKind::kTernaryExpression) {
            auto *ternary = static_cast<BoundTernaryExpression *>(expr.get());
            auto error_expression = std::make_unique<BoundErrorExpression>(
                expr->getSourceLocation(),
                diagnostic::DiagnosticCode::kIncompatibleTypesForTernaryExpression,
                diagnostic::DiagnosticArgs{
                    ternary->getTrueExpression()->getType()->getName(),
                    ternary->getFalseExpression()->getType()->getName()});
            m_context->reportError(error_expression.get());
            static_cast<analysis::VariableSymbol *>(
                variable_symbols[var_idx].get())
                ->setInitializerExpression(std::move(error_expression));
            if (!is_multi)
              expr = nullptr;
          } else if (!is_multi) {
            static_cast<analysis::VariableSymbol *>(
                variable_symbols[var_idx].get())
                ->setInitializerExpression(std::move(expr));
          }
        } else if (*expression_type > *variable_type) {
          auto error_expression = std::make_unique<BoundErrorExpression>(
              expr ? expr->getSourceLocation()
                   : initializer_expression->getSourceLocation(),
              diagnostic::DiagnosticCode::kInitializerExpressionTypeMismatch,
              diagnostic::DiagnosticArgs{variable_type->getName(),
                                         expression_type->getName(),
                                         variable_symbols[var_idx]->getName()});
          m_context->reportError(error_expression.get());
          static_cast<analysis::VariableSymbol *>(
              variable_symbols[var_idx].get())
              ->setInitializerExpression(std::move(error_expression));
          if (!is_multi)
            expr = nullptr;
        } else if (!is_multi) {
          static_cast<analysis::VariableSymbol *>(
              variable_symbols[var_idx].get())
              ->setInitializerExpression(std::move(expr));
        }

        var_idx++;
      }
    }

    while (var_idx < variable_symbols.size()) {
      static_cast<analysis::VariableSymbol *>(variable_symbols[var_idx].get())
          ->setInitializerExpression(
              BinderContext::createDefaultValueExpression(
                  variable_symbols[var_idx]->getType().get(),
                  node->getSourceLocation()));
      var_idx++;
    }

  } else if (node->hasConstKeyword()) {
    auto error_statement = std::make_unique<BoundErrorStatement>(
        node->getSourceLocation(),
        diagnostic::DiagnosticCode::kMissingInitializerExpression,
        diagnostic::DiagnosticArgs{variable_symbols[0]->getName()});
    m_context->reportError(error_statement.get());
    return std::move(error_statement);
  } else {
    for (auto &variable_symbol : variable_symbols) {
      static_cast<analysis::VariableSymbol *>(variable_symbol.get())
          ->setInitializerExpression(
              BinderContext::createDefaultValueExpression(
                  variable_symbol->getType().get(), node->getSourceLocation()));
    }
  }

  return std::make_unique<BoundVariableDeclaration>(
      variable_symbols, std::move(bound_initializer_expressions),
      node->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing