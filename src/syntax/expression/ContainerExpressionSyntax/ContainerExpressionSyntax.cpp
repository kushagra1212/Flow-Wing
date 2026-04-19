/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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

#include "ContainerExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

ContainerExpressionSyntax::ContainerExpressionSyntax(
    const syntax::SyntaxToken *open_bracket,
    std::unique_ptr<ExpressionSyntax> value_expression,
    const syntax::SyntaxToken *close_bracket)
    : m_open_bracket(open_bracket),
      m_value_expression(std::move(value_expression)),
      m_close_bracket(close_bracket) {}

ContainerExpressionSyntax::ContainerExpressionSyntax(
    const syntax::SyntaxToken *open_bracket,
    const syntax::SyntaxToken *close_bracket)
    : m_open_bracket(open_bracket), m_close_bracket(close_bracket) {}

NodeKind ContainerExpressionSyntax::getKind() const {
  return NodeKind::kContainerExpression;
}

void ContainerExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
ContainerExpressionSyntax::getValueExpression() const {
  return m_value_expression;
}

const std::vector<const SyntaxNode *> &
ContainerExpressionSyntax::getChildren() const {

  if (m_children.empty()) {

    if (m_open_bracket) {
      m_children.push_back(m_open_bracket);
    }

    if (m_value_expression) {
      m_children.push_back(m_value_expression.get());
    }

    if (m_close_bracket) {
      m_children.push_back(m_close_bracket);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing