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
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundIfStatement/BoundIfStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/StatementBinder/StatementBinder.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement>
StatementBinder::bindIfStatement(syntax::IfStatementSyntax *statement) {
  assert(statement != nullptr &&
         "BlockStatementBinder::bind: statement is null");

  auto if_statement = static_cast<syntax::IfStatementSyntax *>(statement);

  m_context->getSymbolTable()->enterScope();

  auto bound_if_condition =
      m_expression_binder->bind(if_statement->getConditionExpression().get());

  if (bound_if_condition->getKind() == NodeKind::kErrorExpression) {
    return std::make_unique<BoundErrorStatement>(std::move(bound_if_condition));
  }

  auto bound_if_statement = bind(if_statement->getStatement().get());

  if (bound_if_statement->getKind() == NodeKind::kErrorStatement) {
    return bound_if_statement;
  }

  m_context->getSymbolTable()->leaveScope();

  std::vector<std::unique_ptr<BoundExpression>> or_if_conditions;
  std::vector<std::unique_ptr<BoundStatement>> or_if_statements;

  for (const auto &or_if_statement : if_statement->getOrIfStatements()) {
    m_context->getSymbolTable()->enterScope();

    auto bound_or_if_condition = m_expression_binder->bind(
        or_if_statement->getConditionExpression().get());

    if (bound_or_if_condition->getKind() == NodeKind::kErrorExpression) {
      return std::make_unique<BoundErrorStatement>(
          std::move(bound_or_if_condition));
    }

    auto bound_or_if_statement = bind(or_if_statement->getStatement().get());

    if (bound_or_if_statement->getKind() == NodeKind::kErrorStatement) {
      return bound_or_if_statement;
    }

    or_if_conditions.push_back(std::move(bound_or_if_condition));
    or_if_statements.push_back(std::move(bound_or_if_statement));

    m_context->getSymbolTable()->leaveScope();
  }

  std::unique_ptr<BoundStatement> else_clause = nullptr;

  if (if_statement->getElseClause()) {
    else_clause = bind(if_statement->getElseClause()->getStatement().get());
    if (else_clause->getKind() == NodeKind::kErrorStatement) {
      return else_clause;
    }
  }

  return std::make_unique<BoundIfStatement>(
      std::move(bound_if_condition), std::move(bound_if_statement),
      std::move(or_if_conditions), std::move(or_if_statements),
      std::move(else_clause), if_statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing