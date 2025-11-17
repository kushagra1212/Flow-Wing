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


#include "DefaultCaseStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

DefaultCaseStatementSyntax::DefaultCaseStatementSyntax(
    const SyntaxToken *default_keyword, const SyntaxToken *colon_token,
    std::unique_ptr<StatementSyntax> statement)
    : m_default_keyword(default_keyword), m_colon_token(colon_token),
      m_statement(std::move(statement)) {}

NodeKind DefaultCaseStatementSyntax::getKind() const {
  return NodeKind::kDefaultCaseStatement;
}

void DefaultCaseStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<StatementSyntax> &
DefaultCaseStatementSyntax::getStatement() const {
  return m_statement;
}

const std::vector<const SyntaxNode *> &
DefaultCaseStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &child :
         {static_cast<const SyntaxNode *>(m_default_keyword),
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