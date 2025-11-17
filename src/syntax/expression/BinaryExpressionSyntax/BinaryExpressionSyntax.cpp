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

#include "BinaryExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {
BinaryExpressionSyntax::BinaryExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> left, const SyntaxToken *operator_token,
    std::unique_ptr<ExpressionSyntax> right)
    : m_left(std::move(left)), m_operator_token(operator_token),
      m_right(std::move(right)) {}

// Overrides
NodeKind BinaryExpressionSyntax::getKind() const {
  return NodeKind::kBinaryExpression;
}

void BinaryExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}
// Getters
const SyntaxToken *BinaryExpressionSyntax::getOperatorToken() const {
  return m_operator_token;
}
const std::unique_ptr<ExpressionSyntax> &
BinaryExpressionSyntax::getLeft() const {
  return m_left;
}
const std::unique_ptr<ExpressionSyntax> &
BinaryExpressionSyntax::getRight() const {
  return m_right;
}

const std::vector<const SyntaxNode *> &
BinaryExpressionSyntax::getChildren() const {
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