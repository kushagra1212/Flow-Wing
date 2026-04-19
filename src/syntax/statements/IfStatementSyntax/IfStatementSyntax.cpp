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


#include "IfStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

IfStatementSyntax::IfStatementSyntax(
    const SyntaxToken *if_keyword,
    std::unique_ptr<ExpressionSyntax> condition_expression,
    std::unique_ptr<StatementSyntax> statement,
    std::vector<std::unique_ptr<OrIfStatementSyntax>> or_if_statements,
    std::unique_ptr<ElseClauseSyntax> else_clause)
    : m_if_keyword(if_keyword),
      m_condition_expression(std::move(condition_expression)),
      m_statement(std::move(statement)),
      m_or_if_statements(std::move(or_if_statements)),
      m_else_clause(std::move(else_clause)) {}

NodeKind IfStatementSyntax::getKind() const { return NodeKind::kIfStatement; }

void IfStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
IfStatementSyntax::getConditionExpression() const {
  return m_condition_expression;
}
const std::unique_ptr<StatementSyntax> &
IfStatementSyntax::getStatement() const {
  return m_statement;
}
const std::vector<std::unique_ptr<OrIfStatementSyntax>> &
IfStatementSyntax::getOrIfStatements() const {
  return m_or_if_statements;
}
const std::unique_ptr<ElseClauseSyntax> &
IfStatementSyntax::getElseClause() const {
  return m_else_clause;
}

const std::vector<const SyntaxNode *> &IfStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &node :
         {static_cast<const SyntaxNode *>(m_if_keyword),
          static_cast<const SyntaxNode *>(m_condition_expression.get()),
          static_cast<const SyntaxNode *>(m_statement.get())}) {
      if (node)
        m_children.push_back(node);
    }

    for (const auto &node : m_or_if_statements) {
      if (node)
        m_children.push_back(node.get());
    }

    if (m_else_clause)
      m_children.push_back(m_else_clause.get());
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing