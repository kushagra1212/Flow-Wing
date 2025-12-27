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

#include "BoundErrorExpression.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"

namespace flow_wing {
namespace binding {

BoundErrorExpression::BoundErrorExpression(
    const flow_wing::diagnostic::SourceLocation &location,
    flow_wing::diagnostic::DiagnosticCode code,
    const std::vector<flow_wing::diagnostic::DiagnosticArg> &args)
    : BoundExpression(location), m_code(code), m_args(args) {}

void BoundErrorExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

NodeKind BoundErrorExpression::getKind() const {
  return NodeKind::kErrorExpression;
}

flow_wing::diagnostic::DiagnosticCode BoundErrorExpression::getCode() const {
  return m_code;
}

const std::vector<flow_wing::diagnostic::DiagnosticArg> &
BoundErrorExpression::getArgs() const {
  return m_args;
}

} // namespace binding
} // namespace flow_wing