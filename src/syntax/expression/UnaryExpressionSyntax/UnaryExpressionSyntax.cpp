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

#include "UnaryExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

UnaryExpressionSyntax::UnaryExpressionSyntax(
    const SyntaxToken *operator_token,
    std::unique_ptr<ExpressionSyntax> expression)
    : m_operator_token(operator_token), m_expression(std::move(expression)) {}

NodeKind UnaryExpressionSyntax::getKind() const {
  return NodeKind::kUnaryExpression;
}

void UnaryExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
UnaryExpressionSyntax::getExpression() const {
  return m_expression;
}

lexer::TokenKind UnaryExpressionSyntax::getOperatorTokenKind() const {
  return m_operator_token->getTokenKind();
}

const std::vector<const SyntaxNode *> &
UnaryExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    // Add children
    for (const auto *node :
         {static_cast<const SyntaxNode *>(m_operator_token),
          static_cast<const SyntaxNode *>(m_expression.get())}) {
      if (node) {
        m_children.push_back(node);
      }
    }
  }

  return m_children;
}

} // namespace syntax
} // namespace flow_wing