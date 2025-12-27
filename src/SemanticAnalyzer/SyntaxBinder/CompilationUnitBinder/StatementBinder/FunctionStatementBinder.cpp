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
#include "src/SemanticAnalyzer/BoundStatements/BoundFunctionStatement/BoundFunctionStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ParameterSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/FunctionStatementSyntax/FunctionStatementSyntax.h"
#include "src/syntax/statements/ParameterExpressionSyntax/ParameterExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement> StatementBinder::bindFunctionStatement(
    syntax::FunctionStatementSyntax *statement) {
  assert(statement != nullptr &&
         "FunctionStatementBinder::bind: statement is null");

  auto function_statement =
      static_cast<syntax::FunctionStatementSyntax *>(statement);

  auto function_identifier = static_cast<syntax::IdentifierExpressionSyntax *>(
      function_statement->getIdentifier().get());

  const auto &function_name = function_identifier->getValue();

  const auto &symbol = m_context->getSymbolTable()->lookup(function_name);

  assert(symbol != nullptr && "FunctionStatementBinder::bind: symbol is null");
  assert(symbol->getKind() == analysis::SymbolKind::kFunction &&
         "FunctionStatementBinder::bind: symbol is not a function");

  auto function_symbol = static_cast<analysis::FunctionSymbol *>(symbol.get());

  const auto has_function_body = function_statement->hasBody();

  auto symbol_table = m_context->getSymbolTable().get();

  symbol_table->enterScope();

  auto function_type =
      static_cast<types::FunctionType *>(function_symbol->getType().get());

  assert(function_type != nullptr &&
         "FunctionStatementBinder::bind: function type is null");
  assert(function_type->getParameterTypes().size() ==
             function_statement->getParameters().size() &&
         "FunctionStatementBinder::bind: number of parameters does not match "
         "number of parameter types");

  size_t param_index = 0;

  for (auto &param : function_statement->getParameters()) {

    assert(param != nullptr &&
           "FunctionStatementBinder::bind: parameter is null");
    assert(param->getKind() == syntax::NodeKind::kParameterExpression &&
           "FunctionStatementBinder::bind: parameter is not a parameter "
           "expression");

    auto parameter_expression =
        static_cast<syntax::ParameterExpressionSyntax *>(param.get());

    auto param_identifier =
        parameter_expression->getIdentifierExpression().get();

    assert(param_identifier != nullptr &&
           "FunctionStatementBinder::bind: parameter identifier is null");
    assert(param_identifier->getKind() ==
               syntax::NodeKind::kIdentifierExpression &&
           "FunctionStatementBinder::bind: parameter identifier is not an "
           "identifier expression");

    auto param_identifier_expression =
        static_cast<syntax::IdentifierExpressionSyntax *>(param_identifier);

    const auto param_identifier_name = param_identifier_expression->getValue();

    auto param_type = function_type->getParameterTypes()[param_index];

    assert(param_type != nullptr &&
           "FunctionStatementBinder::bind: parameter type is null");

    const auto has_default_value =
        parameter_expression->hasDefaultValueExpression();
    std::unique_ptr<binding::BoundExpression> bound_default_value_expression =
        nullptr;

    auto const is_function_decl_param_has_default_value =
        has_default_value && !has_function_body;

    if (is_function_decl_param_has_default_value) {
      auto error_statement = std::make_unique<BoundErrorStatement>(
          parameter_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::
              kFunctionDeclarationDoesNotAllowDefaultParameterValues,
          diagnostic::DiagnosticArgs{param_identifier_name, function_name});
      m_context->reportError(error_statement.get());
      return std::move(error_statement);
    }

    if (has_default_value) {
      bound_default_value_expression = m_expression_binder->bind(
          parameter_expression->getDefaultValueExpression().get());

      if (bound_default_value_expression->getKind() ==
          NodeKind::kErrorExpression) {
        return std::make_unique<BoundErrorStatement>(
            std::move(bound_default_value_expression));
      }
    }

    auto param_symbol = std::make_shared<analysis::ParameterSymbol>(
        param_identifier_name, param_type->type,
        std::move(bound_default_value_expression));

    if (!symbol_table->define(param_symbol)) {

      auto error_statement = std::make_unique<BoundErrorStatement>(
          parameter_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kParameterAlreadyDeclared,
          diagnostic::DiagnosticArgs{param_identifier_name, function_name});
      m_context->reportError(error_statement.get());
      return std::move(error_statement);
    }

    function_symbol->addParameter(param_symbol);

    param_index++;
  }

  if (has_function_body) {

    symbol_table->setCurrentFunctionSymbol(function_symbol);

    auto bound_function_body =
        bindBlockStatement(static_cast<syntax::BlockStatementSyntax *>(
            function_statement->getBody().get()));

    if (bound_function_body->getKind() == NodeKind::kErrorStatement) {
      return bound_function_body;
    }

    symbol_table->setCurrentFunctionSymbol(nullptr);

    function_symbol->setBody(std::move(bound_function_body));
  }

  symbol_table->leaveScope();

  return std::make_unique<BoundFunctionStatement>(
      std::vector<std::shared_ptr<analysis::Symbol>>({symbol}),
      function_statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing