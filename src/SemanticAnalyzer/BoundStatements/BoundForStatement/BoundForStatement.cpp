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

#include "BoundForStatement.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"

namespace flow_wing {
namespace binding {

BoundForStatement::BoundForStatement(
    std::unique_ptr<BoundStatement> variable_declaration,
    std::unique_ptr<BoundExpression> assignment_expression,
    std::unique_ptr<BoundExpression> upper_bound,
    std::unique_ptr<BoundExpression> step, std::unique_ptr<BoundStatement> body,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundStatement(location),
      m_variable_declaration(std::move(variable_declaration)),
      m_assignment_expression(std::move(assignment_expression)),
      m_upper_bound(std::move(upper_bound)), m_step(std::move(step)),
      m_body(std::move(body)) {}

NodeKind BoundForStatement::getKind() const { return NodeKind::kForStatement; }

void BoundForStatement::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

} // namespace binding
} // namespace flow_wing