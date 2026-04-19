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

#include "DeclaratorExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

DeclaratorExpressionSyntax::DeclaratorExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> identifier_expression,
    const SyntaxToken *colon_token,
    std::unique_ptr<ExpressionSyntax> type_expression)
    : ExpressionSyntax(identifier_expression->getSourceLocation()),
      m_identifier_expression(std::move(identifier_expression)),
      m_colon_token(colon_token),
      m_type_expression(std::move(type_expression)) {}

syntax::NodeKind DeclaratorExpressionSyntax::getKind() const {
  return NodeKind::kDeclaratorExpression;
}

void DeclaratorExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}
// getters

const std::unique_ptr<ExpressionSyntax> &
DeclaratorExpressionSyntax::getIdentifierExpression() const {
  return m_identifier_expression;
}

const std::unique_ptr<ExpressionSyntax> &
DeclaratorExpressionSyntax::getTypeExpression() const {
  return m_type_expression;
}

const std::vector<const SyntaxNode *> &
DeclaratorExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto *node :
         {static_cast<const SyntaxNode *>(m_identifier_expression.get()),
          static_cast<const SyntaxNode *>(m_colon_token),
          static_cast<const SyntaxNode *>(m_type_expression.get())}) {
      if (node) {
        m_children.push_back(node);
      }
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing