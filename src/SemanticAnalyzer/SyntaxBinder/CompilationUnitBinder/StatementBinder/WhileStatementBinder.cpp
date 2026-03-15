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
#include "src/SemanticAnalyzer/BoundStatements/BoundWhileStatement/BoundWhileStatement.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/StatementBinder/StatementBinder.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "src/syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement>
StatementBinder::bindWhileStatement(syntax::WhileStatementSyntax *statement) {
  assert(statement != nullptr &&
         "WhileStatementBinder::bind: statement is null");

  auto while_statement = static_cast<syntax::WhileStatementSyntax *>(statement);

  m_context->getSymbolTable()->enterScope();
  m_context->getSymbolTable()->pushBreakScope();

  auto while_condition =
      m_expression_binder->bind(while_statement->getCondition().get());

  if (while_condition->getKind() == NodeKind::kErrorExpression) {
    m_context->getSymbolTable()->popBreakScope();
    m_context->getSymbolTable()->leaveScope();
    return std::make_unique<BoundErrorStatement>(std::move(while_condition));
  }

  auto bound_while_statement = bind(while_statement->getStatement().get());

  if (bound_while_statement->getKind() == NodeKind::kErrorStatement) {
    m_context->getSymbolTable()->popBreakScope();
    m_context->getSymbolTable()->leaveScope();
    return bound_while_statement;
  }

  m_context->getSymbolTable()->popBreakScope();
  m_context->getSymbolTable()->leaveScope();

  return std::make_unique<BoundWhileStatement>(
      std::move(while_condition), std::move(bound_while_statement),
      while_statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing