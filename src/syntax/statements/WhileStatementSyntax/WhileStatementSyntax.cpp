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


#include "WhileStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

WhileStatementSyntax::WhileStatementSyntax(
    const SyntaxToken *while_keyword,
    std::unique_ptr<ExpressionSyntax> condition,
    std::unique_ptr<StatementSyntax> statement)
    : m_while_keyword(while_keyword), m_condition(std::move(condition)),
      m_statement(std::move(statement)) {}

NodeKind WhileStatementSyntax::getKind() const {
  return NodeKind::kWhileStatement;
}

void WhileStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
WhileStatementSyntax::getCondition() const {
  return m_condition;
}
const std::unique_ptr<StatementSyntax> &
WhileStatementSyntax::getStatement() const {
  return m_statement;
}

const std::vector<const SyntaxNode *> &
WhileStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &node :
         {static_cast<const SyntaxNode *>(m_while_keyword),
          static_cast<const SyntaxNode *>(m_condition.get()),
          static_cast<const SyntaxNode *>(m_statement.get())}) {
      if (node)
        m_children.push_back(node);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing