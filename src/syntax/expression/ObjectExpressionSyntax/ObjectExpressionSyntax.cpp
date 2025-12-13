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

#include "ObjectExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

ObjectExpressionSyntax::ObjectExpressionSyntax(
    const SyntaxToken *open_brace_token,
    std::vector<std::unique_ptr<ObjectMemberSyntax>> members,
    std::vector<const SyntaxToken *> comma_tokens,
    const SyntaxToken *close_brace_token)
    : ExpressionSyntax(open_brace_token->getSourceLocation()),
      m_open_brace_token(open_brace_token), m_members(std::move(members)),
      m_comma_tokens(std::move(comma_tokens)),
      m_close_brace_token(close_brace_token) {}

NodeKind ObjectExpressionSyntax::getKind() const {
  return NodeKind::kObjectExpression;
}

void ObjectExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<std::unique_ptr<ObjectMemberSyntax>> &
ObjectExpressionSyntax::getMembers() const {
  return m_members;
}

const std::vector<const SyntaxNode *> &
ObjectExpressionSyntax::getChildren() const {
  if (m_children.empty()) {

    m_children.push_back(m_open_brace_token);

    size_t size = std::max(m_members.size(), m_comma_tokens.size());

    for (size_t i = 0; i < size; i++) {
      if (i < m_members.size() && m_members[i]) {
        m_children.push_back(m_members[i].get());
      }
      if (i < m_comma_tokens.size() && m_comma_tokens[i]) {
        m_children.push_back(m_comma_tokens[i]);
      }
    }
    m_children.push_back(m_close_brace_token);
  }

  return m_children;
}

} // namespace syntax
} // namespace flow_wing