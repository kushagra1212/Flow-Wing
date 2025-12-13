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
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

IdentifierExpressionSyntax::IdentifierExpressionSyntax(
    const SyntaxToken *identifier_token)
    : m_identifier_token(identifier_token),
      m_value(identifier_token->getText()) {}

// Overrides
NodeKind IdentifierExpressionSyntax::getKind() const {
  return NodeKind::kIdentifierExpression;
}

void IdentifierExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
IdentifierExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    if (m_identifier_token)
      m_children.emplace_back(m_identifier_token);
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing