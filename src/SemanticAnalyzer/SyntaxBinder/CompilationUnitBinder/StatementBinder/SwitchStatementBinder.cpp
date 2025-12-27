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
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundSwitchStatement/BoundSwitchStatement.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/Type.hpp"
#include "src/syntax/statements/CaseStatementSyntax/CaseStatementSyntax.h"
#include "src/syntax/statements/DefaultCaseStatementSyntax/DefaultCaseStatementSyntax.h"
#include "src/syntax/statements/SwitchStatementSyntax/SwitchStatementSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement>
StatementBinder::bindSwitchStatement(syntax::SwitchStatementSyntax *statement) {
  assert(statement != nullptr &&
         "SwitchStatementBinder::bind: statement is null");

  auto switch_statement =
      static_cast<syntax::SwitchStatementSyntax *>(statement);

  m_context->getSymbolTable()->enterScope();

  auto bound_switch_condition_expression = m_expression_binder->bind(
      switch_statement->getSwitchConditionExpression().get());

  auto condition_type = bound_switch_condition_expression->getType();

  if (bound_switch_condition_expression->getKind() ==
      NodeKind::kErrorExpression) {
    return std::make_unique<BoundErrorStatement>(
        std::move(bound_switch_condition_expression));
  }
  std::unique_ptr<BoundStatement> bound_default_case_statement = nullptr;

  std::vector<std::unique_ptr<BoundExpression>> bound_case_expressions;
  std::vector<std::unique_ptr<BoundStatement>> bound_case_statements;

  for (const auto &case_statement : switch_statement->getCaseStatements()) {
    if (case_statement->getKind() == syntax::NodeKind::kDefaultCaseStatement) {
      if (bound_default_case_statement != nullptr) {
        auto error_statement = std::make_unique<BoundErrorStatement>(
            case_statement->getSourceLocation(),
            diagnostic::DiagnosticCode::kMultipleDefaultCaseStatements,
            diagnostic::DiagnosticArgs{});
        m_context->reportError(error_statement.get());
        return std::move(error_statement);
      }

      auto default_case_statement_syntax =
          static_cast<syntax::DefaultCaseStatementSyntax *>(
              case_statement.get());

      m_context->getSymbolTable()->enterScope();

      bound_default_case_statement =
          bind(default_case_statement_syntax->getStatement().get());

      m_context->getSymbolTable()->leaveScope();

      if (bound_default_case_statement->getKind() ==
          NodeKind::kErrorStatement) {
        return bound_default_case_statement;
      }

    } else {
      auto case_statement_syntax =
          static_cast<syntax::CaseStatementSyntax *>(case_statement.get());

      auto bound_case_expression = m_expression_binder->bind(
          case_statement_syntax->getCaseExpression().get());

      if (bound_case_expression->getKind() == NodeKind::kErrorExpression) {
        return std::make_unique<BoundErrorStatement>(
            std::move(bound_case_expression));
      }

      auto case_expression_type = bound_case_expression->getType();

      if (case_expression_type != condition_type) {
        auto error_statement = std::make_unique<BoundErrorStatement>(
            case_statement->getSourceLocation(),
            diagnostic::DiagnosticCode::kCaseExpressionTypeMismatch,
            diagnostic::DiagnosticArgs{
                condition_type->getName(),
                case_expression_type->getName(),
            });
        m_context->reportError(error_statement.get());
        return std::move(error_statement);
      }

      bound_case_expressions.push_back(std::move(bound_case_expression));

      m_context->getSymbolTable()->enterScope();

      auto bound_case_statement =
          bind(case_statement_syntax->getStatement().get());

      m_context->getSymbolTable()->leaveScope();

      if (bound_case_statement->getKind() == NodeKind::kErrorStatement) {
        return bound_case_statement;
      }

      bound_case_statements.push_back(std::move(bound_case_statement));
    }
  }

  m_context->getSymbolTable()->leaveScope();

  return std::make_unique<BoundSwitchStatement>(
      std::move(bound_switch_condition_expression),
      std::move(bound_default_case_statement),
      std::move(bound_case_expressions), std::move(bound_case_statements),
      switch_statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing
