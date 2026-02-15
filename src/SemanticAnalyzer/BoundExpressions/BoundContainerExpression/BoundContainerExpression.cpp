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

#include "BoundContainerExpression.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include <cassert>

namespace flow_wing {
namespace binding {

BoundContainerExpressionElement::BoundContainerExpressionElement(
    std::unique_ptr<BoundExpression> expression)
    : m_expression(std::move(expression)) {}

void BoundContainerExpressionElement::addIndex(size_t index) {
  m_indices.push_front(index);
}

const std::deque<size_t> &BoundContainerExpressionElement::getIndices() const {
  return m_indices;
}

std::unique_ptr<BoundExpression> &
BoundContainerExpressionElement::getExpression() {
  return m_expression;
}

BoundContainerExpression::BoundContainerExpression(
    std::vector<std::unique_ptr<BoundContainerExpressionElement>> elements,
    std::shared_ptr<types::ArrayType> type, bool is_default_value,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_elements(std::move(elements)),
      m_type(std::move(type)), m_is_default_value(is_default_value) {}

NodeKind BoundContainerExpression::getKind() const {
  return NodeKind::kContainerExpression;
}

void BoundContainerExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

std::shared_ptr<types::Type> BoundContainerExpression::getType() const {
  return m_type;
}

bool BoundContainerExpression::isDefaultValue() const {
  return m_is_default_value;
}

std::vector<std::unique_ptr<BoundContainerExpressionElement>> &
BoundContainerExpression::getElements() {
  return m_elements;
}

} // namespace binding
} // namespace flow_wing