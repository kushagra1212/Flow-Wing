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


#include "CaseStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

CaseStatementSyntax::CaseStatementSyntax(
    const SyntaxToken *case_token,
    std::unique_ptr<ExpressionSyntax> case_expression,
    const SyntaxToken *colon_token, std::unique_ptr<StatementSyntax> statement)
    : m_case_token(case_token), m_case_expression(std::move(case_expression)),
      m_colon_token(colon_token), m_statement(std::move(statement)) {}

NodeKind CaseStatementSyntax::getKind() const {
  return NodeKind::kCaseStatement;
}

void CaseStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
CaseStatementSyntax::getCaseExpression() const {
  return m_case_expression;
}

const std::unique_ptr<StatementSyntax> &
CaseStatementSyntax::getStatement() const {
  return m_statement;
}

const std::vector<const SyntaxNode *> &
CaseStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &child :
         {static_cast<const SyntaxNode *>(m_case_token),
          static_cast<const SyntaxNode *>(m_case_expression.get()),
          static_cast<const SyntaxNode *>(m_colon_token),
          static_cast<const SyntaxNode *>(m_statement.get())}) {
      if (child)
        m_children.push_back(child);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing