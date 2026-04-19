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


#include "OrIfStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

OrIfStatementSyntax::OrIfStatementSyntax(
    const SyntaxToken *or_keyword, const SyntaxToken *if_keyword,
    std::unique_ptr<ExpressionSyntax> condition_expression,
    std::unique_ptr<StatementSyntax> statement)
    : m_or_keyword(or_keyword), m_if_keyword(if_keyword),
      m_condition_expression(std::move(condition_expression)),
      m_statement(std::move(statement)) {}

NodeKind OrIfStatementSyntax::getKind() const {
  return NodeKind::kOrIfStatement;
}

void OrIfStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
OrIfStatementSyntax::getConditionExpression() const {
  return m_condition_expression;
}
const std::unique_ptr<StatementSyntax> &
OrIfStatementSyntax::getStatement() const {
  return m_statement;
}
const std::vector<const SyntaxNode *> &
OrIfStatementSyntax::getChildren() const {
  if (m_children.empty()) {

    for (const auto &node :
         {static_cast<const SyntaxNode *>(m_or_keyword),
          static_cast<const SyntaxNode *>(m_if_keyword),
          static_cast<const SyntaxNode *>(m_condition_expression.get()),
          static_cast<const SyntaxNode *>(m_statement.get())}) {
      if (node)
        m_children.push_back(node);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing