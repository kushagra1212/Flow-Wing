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

#include "BoundAssignmentExpression.h"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"

namespace flow_wing {
namespace binding {

BoundAssignmentExpression::BoundAssignmentExpression(
    std::vector<std::unique_ptr<BoundExpression>> left,
    std::vector<std::unique_ptr<BoundExpression>> right,
    bool is_full_re_assignment,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_left(std::move(left)),
      m_right(std::move(right)),
      m_is_full_re_assignment(is_full_re_assignment) {}

NodeKind BoundAssignmentExpression::getKind() const {
  return NodeKind::kAssignmentExpression;
}

void BoundAssignmentExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

bool BoundAssignmentExpression::isMultiTargetAssignment() const {
  return m_left.size() > 1;
}

std::shared_ptr<types::Type> BoundAssignmentExpression::getType() const {
  return m_left[0]->getType();
}

} // namespace binding
} // namespace flow_wing