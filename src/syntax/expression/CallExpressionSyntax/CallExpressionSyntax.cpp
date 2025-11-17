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

#include "CallExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"

namespace flow_wing {
namespace syntax {

CallExpressionSyntax::CallExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> identifier,
    const syntax::SyntaxToken *open_parenthesis_token,
    std::unique_ptr<ExpressionSyntax> argument_expression,
    const syntax::SyntaxToken *close_parenthesis_token)
    : m_identifier(std::move(identifier)),
      m_open_parenthesis_token(open_parenthesis_token),
      m_argument_expression(std::move(argument_expression)),
      m_close_parenthesis_token(close_parenthesis_token) {}

NodeKind CallExpressionSyntax::getKind() const {
  return NodeKind::kCallExpression;
}

void CallExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
CallExpressionSyntax::getIdentifier() const {
  return m_identifier;
}

const std::unique_ptr<ExpressionSyntax> &
CallExpressionSyntax::getArgumentExpression() const {
  return m_argument_expression;
}

const std::vector<const SyntaxNode *> &
CallExpressionSyntax::getChildren() const {

  if (m_children.empty()) {

    for (const auto *node :
         {static_cast<const SyntaxNode *>(m_identifier.get()),
          static_cast<const SyntaxNode *>(m_open_parenthesis_token)}) {
      if (node) {
        m_children.push_back(node);
      }
    }

    if (m_argument_expression) {
      m_children.push_back(m_argument_expression.get());
    }

    if (m_close_parenthesis_token) {
      m_children.push_back(m_close_parenthesis_token);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing