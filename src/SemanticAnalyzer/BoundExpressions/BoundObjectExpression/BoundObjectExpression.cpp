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

#include "BoundObjectExpression.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include <cassert>

namespace flow_wing {
namespace binding {

BoundObjectExpression::BoundObjectExpression(
    std::map<std::string, std::shared_ptr<types::Type>> field_types_map,
    std::vector<std::unique_ptr<BoundExpression>> colon_expressions,
    std::shared_ptr<types::Type> type,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_field_types_map(std::move(field_types_map)),
      m_colon_expressions(std::move(colon_expressions)), m_type(type) {}

NodeKind BoundObjectExpression::getKind() const {
  return NodeKind::kObjectExpression;
}

void BoundObjectExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

std::shared_ptr<types::Type> BoundObjectExpression::getType() const {
  assert(m_type && "Object Expression type is null");
  return m_type;
}

void BoundObjectExpression::setType(std::shared_ptr<types::Type> type) {
  m_type = type;
}

const std::map<std::string, std::shared_ptr<types::Type>> &
BoundObjectExpression::getFieldTypesMap() const {
  return m_field_types_map;
}
const std::vector<std::unique_ptr<BoundExpression>> &
BoundObjectExpression::getColonExpressions() const {
  return m_colon_expressions;
}

} // namespace binding
} // namespace flow_wing