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

#include "ParenthesizedExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(
    const SyntaxToken *open_parenthesis_token,
    std::unique_ptr<ExpressionSyntax> expression,
    const SyntaxToken *close_parenthesis_token)
    : m_open_parenthesis_token(open_parenthesis_token),
      m_expression(std::move(expression)),
      m_close_parenthesis_token(std::move(close_parenthesis_token)) {}

// Overrides

syntax::NodeKind ParenthesizedExpressionSyntax::getKind() const {
  return NodeKind::kParenthesizedExpression;
}

const std::unique_ptr<ExpressionSyntax> &
ParenthesizedExpressionSyntax::getExpression() const {
  return m_expression;
}

void ParenthesizedExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
ParenthesizedExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &child :
         {static_cast<const SyntaxNode *>(m_open_parenthesis_token),
          static_cast<const SyntaxNode *>(m_expression.get()),
          static_cast<const SyntaxNode *>(m_close_parenthesis_token)}) {
      if (child) {
        m_children.push_back(child);
      }
    }
  }

  return m_children;
}

} // namespace syntax

} // namespace flow_wing