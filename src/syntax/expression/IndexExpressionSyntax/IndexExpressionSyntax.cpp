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

#include "IndexExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

IndexExpressionSyntax::IndexExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> left_expression,
    std::vector<std::unique_ptr<ExpressionSyntax>> dimension_clause_expressions)
    : m_left_expression(std::move(left_expression)),
      m_dimension_clause_expressions(std::move(dimension_clause_expressions)) {}

NodeKind IndexExpressionSyntax::getKind() const {
  return NodeKind::kIndexExpression;
}

void IndexExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
IndexExpressionSyntax::getLeftExpression() const {
  return m_left_expression;
}

const std::vector<std::unique_ptr<ExpressionSyntax>> &
IndexExpressionSyntax::getDimensionClauseExpressions() const {
  return m_dimension_clause_expressions;
}

const std::vector<const SyntaxNode *> &
IndexExpressionSyntax::getChildren() const {

  if (m_children.empty()) {

    if (m_left_expression)
      m_children.emplace_back(this->m_left_expression.get());

    for (const auto &item : this->m_dimension_clause_expressions) {
      if (item)
        m_children.emplace_back(item.get());
    }
  }
  return m_children;
}
} // namespace syntax

} // namespace flow_wing