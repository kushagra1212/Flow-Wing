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

#include "AssignmentExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"
#include <cstddef>

namespace flow_wing {
namespace syntax {

AssignmentExpressionSyntax::AssignmentExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> left, const SyntaxToken *operator_token,
    std::unique_ptr<ExpressionSyntax> right)
    : m_left(std::move(left)), m_operator_token(operator_token),
      m_right(std::move(right)) {}

// Overrides

NodeKind AssignmentExpressionSyntax::getKind() const {
  return NodeKind::kAssignmentExpression;
}

void AssignmentExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

// Boolean Queries
bool AssignmentExpressionSyntax::isFullReAssignment() const {
  return m_operator_token->getTokenKind() == lexer::TokenKind::kLeftArrowToken;
}

// Getters
const std::unique_ptr<ExpressionSyntax> &
AssignmentExpressionSyntax::getLeft() const {
  return m_left;
}
const std::unique_ptr<ExpressionSyntax> &
AssignmentExpressionSyntax::getRight() const {
  return m_right;
}

const SyntaxToken *AssignmentExpressionSyntax::getOperatorToken() const {
  return m_operator_token;
}

const std::vector<const SyntaxNode *> &
AssignmentExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto *node : {static_cast<const SyntaxNode *>(m_left.get()),
                             static_cast<const SyntaxNode *>(m_operator_token),
                             static_cast<const SyntaxNode *>(m_right.get())}) {
      if (node) {
        m_children.push_back(node);
      }
    }
  }

  return m_children;
}

} // namespace syntax
} // namespace flow_wing