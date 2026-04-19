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

#include "BoundColonExpression.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include <cassert>

namespace flow_wing {
namespace binding {

BoundColonExpression::BoundColonExpression(
    const std::string &field_name,
    std::unique_ptr<BoundExpression> right_expression,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_field_name(field_name),
      m_right_expression(std::move(right_expression)) {}

NodeKind BoundColonExpression::getKind() const {
  return NodeKind::kColonExpression;
}

void BoundColonExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

std::shared_ptr<types::Type> BoundColonExpression::getType() const {
  return m_right_expression->getType();
}

const std::string &BoundColonExpression::getFieldName() const {
  return m_field_name;
}

const std::unique_ptr<BoundExpression> &
BoundColonExpression::getRightExpression() const {
  return m_right_expression;
}

} // namespace binding
} // namespace flow_wing