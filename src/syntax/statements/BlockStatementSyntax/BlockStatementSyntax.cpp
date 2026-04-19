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


#include "BlockStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

BlockStatementSyntax::BlockStatementSyntax(
    const SyntaxToken *open_brace_token,
    std::vector<std::unique_ptr<StatementSyntax>> statements,
    const SyntaxToken *close_brace_token)
    : m_open_brace_token(open_brace_token), m_statements(std::move(statements)),
      m_close_brace_token(close_brace_token) {}

NodeKind BlockStatementSyntax::getKind() const {
  return NodeKind::kBlockStatement;
}

void BlockStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<std::unique_ptr<StatementSyntax>> &
BlockStatementSyntax::getStatements() const {
  return m_statements;
}

const std::vector<const SyntaxNode *> &
BlockStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    if (m_open_brace_token)
      m_children.push_back(m_open_brace_token);

    for (const auto &statement : m_statements) {
      if (statement)
        m_children.push_back(statement.get());
    }

    if (m_close_brace_token)
      m_children.push_back(m_close_brace_token);
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing