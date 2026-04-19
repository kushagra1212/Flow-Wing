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

#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundTemplateStringLiteralExpression/BoundTemplateStringLiteralExpression.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"

namespace flow_wing {
namespace binding {

BoundTemplateStringLiteralExpression::BoundTemplateStringLiteralExpression(
    std::string string_value, std::shared_ptr<types::Type> type,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_value(string_value), m_type(type) {}

NodeKind BoundTemplateStringLiteralExpression::getKind() const {
  return NodeKind::kTemplateStringLiteralExpression;
}

void BoundTemplateStringLiteralExpression::accept(
    visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

const std::string &BoundTemplateStringLiteralExpression::getValue() const {
  return m_value;
}

std::shared_ptr<types::Type>
BoundTemplateStringLiteralExpression::getType() const {
  return m_type;
}

} // namespace binding
} // namespace flow_wing