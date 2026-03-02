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

#include "BoundIndexExpression.h"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/common/Symbol/Symbol.hpp"

namespace flow_wing {
namespace binding {

BoundIndexExpression::BoundIndexExpression(
    std::unique_ptr<BoundExpression> left_expression,
    std::shared_ptr<types::Type> type,
    std::vector<std::unique_ptr<BoundExpression>> dimension_clause_expressions,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_left_expression(std::move(left_expression)),
      m_type(type),
      m_dimension_clause_expressions(std::move(dimension_clause_expressions)) {}

NodeKind BoundIndexExpression::getKind() const {
  return NodeKind::kIndexExpression;
}

void BoundIndexExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

std::shared_ptr<types::Type> BoundIndexExpression::getType() const {
  return m_type;
}

const std::unique_ptr<BoundExpression> &
BoundIndexExpression::getLeftExpression() const {
  return m_left_expression;
}

const std::vector<std::unique_ptr<BoundExpression>> &
BoundIndexExpression::getDimensionClauseExpressions() const {
  return m_dimension_clause_expressions;
}

} // namespace binding
} // namespace flow_wing