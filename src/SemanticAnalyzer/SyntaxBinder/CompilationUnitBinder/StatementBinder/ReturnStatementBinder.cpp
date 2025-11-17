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
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundBreakStatement/BoundBreakStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundReturnStatement/BoundReturnStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "src/syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement>
StatementBinder::bindReturnStatement(syntax::ReturnStatementSyntax *statement) {
  assert(statement != nullptr &&
         "ReturnStatementBinder::bind: statement is null");

  auto return_statement =
      static_cast<syntax::ReturnStatementSyntax *>(statement);

  auto symbol_table = m_context->getSymbolTable().get();

  if (symbol_table->isInReturnScope()) {
    m_context->reportError(
        diagnostic::DiagnosticCode::kReturnStatementNotInFunction, {},
        return_statement->getSourceLocation());
    return std::make_unique<BoundErrorStatement>(
        return_statement->getSourceLocation());
  }

  std::vector<std::unique_ptr<BoundExpression>> return_expressions;
  auto current_function_symbol = symbol_table->getCurrentFunctionSymbol();

  if (return_statement->getReturnExpression().get()) {

    return_expressions = m_expression_binder->bindExpressionList(
        return_statement->getReturnExpression().get());
  }

  auto function_type = static_cast<types::FunctionType *>(
      current_function_symbol->getType().get());

  if (!return_expressions.empty()) {
    if (return_expressions.size() != function_type->getReturnTypes().size()) {
      m_context->reportError(
          diagnostic::DiagnosticCode::kInvalidNumberOfReturnExpressions,
          {std::to_string(function_type->getReturnTypes().size()),
           std::to_string(return_expressions.size())},
          return_statement->getSourceLocation());
      return std::make_unique<BoundErrorStatement>(
          return_statement->getSourceLocation());
    }

    size_t count = return_expressions.size();

    for (size_t i = 0; i < count; i++) {
      auto return_expression = return_expressions[i].get();
      auto return_type = function_type->getReturnTypes()[i]->type;

      if (return_expression->getType() != return_type) {
        m_context->reportError(
            diagnostic::DiagnosticCode::kReturnExpressionTypeMismatch,
            {return_expression->getType()->getName(), return_type->getName()},
            return_statement->getSourceLocation());

        return std::make_unique<BoundErrorStatement>(
            return_statement->getSourceLocation());
      }
    }
  } else if (function_type->getReturnTypes().size() == 1 &&
             function_type->getReturnTypes().back()->type !=
                 analysis::Builtins::m_nthg_type_instance) {
    m_context->reportError(
        diagnostic::DiagnosticCode::kReturnExpressionTypeMismatch,
        {
            analysis::Builtins::m_nthg_type_instance->getName(),
            function_type->getReturnTypes().back()->type->getName(),
        },
        return_statement->getSourceLocation());
    return std::make_unique<BoundErrorStatement>(
        return_statement->getSourceLocation());
  } else if (function_type->getReturnTypes().size() > 1) {

    m_context->reportError(
        diagnostic::DiagnosticCode::kInvalidNumberOfReturnExpressions,
        {
            std::to_string(1),
            std::to_string(function_type->getReturnTypes().size()),
        },
        return_statement->getSourceLocation());

    return std::make_unique<BoundErrorStatement>(
        return_statement->getSourceLocation());
  }

  return std::make_unique<BoundReturnStatement>(
      std::move(return_expressions), return_statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing