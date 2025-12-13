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

#include "BoundMemberAccessExpression.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"

namespace flow_wing {
namespace binding {

BoundMemberAccessExpression::BoundMemberAccessExpression(
    types::CustomObjectType *object_type, const std::string &member_name,
    std::shared_ptr<types::Type> field_type,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_object_type(object_type),
      m_member_name(member_name), m_field_type(field_type) {}

NodeKind BoundMemberAccessExpression::getKind() const {
  return NodeKind::kMemberAccessExpression;
}

void BoundMemberAccessExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

std::shared_ptr<types::Type> BoundMemberAccessExpression::getType() const {
  return m_field_type;
}

} // namespace binding
} // namespace flow_wing