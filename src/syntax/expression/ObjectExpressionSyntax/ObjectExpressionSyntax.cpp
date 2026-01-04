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

#include "ObjectExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

ObjectExpressionSyntax::ObjectExpressionSyntax(
    const SyntaxToken *open_brace_token,
    std::unique_ptr<ExpressionSyntax> colon_expression,
    const SyntaxToken *close_brace_token)
    : m_open_brace_token(open_brace_token),
      m_colon_expression(std::move(colon_expression)),
      m_close_brace_token(close_brace_token) {}

NodeKind ObjectExpressionSyntax::getKind() const {
  return NodeKind::kObjectExpression;
}

void ObjectExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
ObjectExpressionSyntax::getColonExpression() const {
  return m_colon_expression;
}

const std::vector<const SyntaxNode *> &
ObjectExpressionSyntax::getChildren() const {
  if (m_children.empty()) {

    m_children.push_back(m_open_brace_token);

    m_children.push_back(m_colon_expression.get());

    m_children.push_back(m_close_brace_token);
  }

  return m_children;
}

} // namespace syntax
} // namespace flow_wing