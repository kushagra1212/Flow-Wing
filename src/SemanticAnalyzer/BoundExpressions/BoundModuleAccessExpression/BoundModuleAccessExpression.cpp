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


#include "BoundModuleAccessExpression.hpp"

namespace flow_wing {
namespace binding {

BoundModuleAccessExpression::BoundModuleAccessExpression(
    analysis::Symbol *symbol,
    std::unique_ptr<BoundExpression> member_access_expression,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_symbol(symbol),
      m_member_access_expression(std::move(member_access_expression)) {}

NodeKind BoundModuleAccessExpression::getKind() const {
  return NodeKind::kModuleAccessExpression;
}

std::shared_ptr<types::Type> BoundModuleAccessExpression::getType() const {
  return m_member_access_expression->getType();
}

analysis::Symbol *BoundModuleAccessExpression::getSymbol() const {
  return m_symbol;
}

const std::unique_ptr<BoundExpression> &
BoundModuleAccessExpression::getMemberAccessExpression() const {
  return m_member_access_expression;
}

} // namespace binding
} // namespace flow_wing