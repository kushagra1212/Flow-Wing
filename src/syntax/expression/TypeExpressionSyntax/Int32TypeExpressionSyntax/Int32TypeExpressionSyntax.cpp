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


#include "Int32TypeExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

Int32TypeExpressionSyntax::Int32TypeExpressionSyntax(
    const SyntaxToken *int32_token)
    : m_int32_token(int32_token) {}

NodeKind Int32TypeExpressionSyntax::getKind() const {
  return NodeKind::kInt32TypeExpression;
}

void Int32TypeExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
Int32TypeExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    if (m_int32_token)
      m_children.emplace_back(m_int32_token);
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing