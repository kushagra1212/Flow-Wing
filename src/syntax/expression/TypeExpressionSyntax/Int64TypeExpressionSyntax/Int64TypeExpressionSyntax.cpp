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


#include "Int64TypeExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

Int64TypeExpressionSyntax::Int64TypeExpressionSyntax(
    const SyntaxToken *int64_token)
    : m_int64_token(int64_token) {}

NodeKind Int64TypeExpressionSyntax::getKind() const {
  return NodeKind::kInt64TypeExpression;
}

void Int64TypeExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
Int64TypeExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    if (m_int64_token)
      m_children.emplace_back(m_int64_token);
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing