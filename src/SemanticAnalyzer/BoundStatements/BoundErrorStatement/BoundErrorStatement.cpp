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

#include "BoundErrorStatement.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include <cassert>

namespace flow_wing {
namespace binding {

BoundErrorStatement::BoundErrorStatement(
    const flow_wing::diagnostic::SourceLocation &location,
    flow_wing::diagnostic::DiagnosticCode code,
    const std::vector<flow_wing::diagnostic::DiagnosticArg> &args)
    : BoundStatement(location), m_code(code), m_args(args) {}

BoundErrorStatement::BoundErrorStatement(
    std::unique_ptr<BoundExpression> expression)
    : BoundStatement(expression->getSourceLocation()) {

  assert(expression->getKind() == NodeKind::kErrorExpression &&
         "BoundErrorStatement::BoundErrorStatement: expression is not a "
         "BoundErrorExpression");

  auto error_expression = static_cast<BoundErrorExpression *>(expression.get());
  m_code = error_expression->getCode();
  m_args = error_expression->getArgs();
}

NodeKind BoundErrorStatement::getKind() const {
  return NodeKind::kErrorStatement;
}

void BoundErrorStatement::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

flow_wing::diagnostic::DiagnosticCode BoundErrorStatement::getCode() const {
  return m_code;
}

const std::vector<flow_wing::diagnostic::DiagnosticArg> &
BoundErrorStatement::getArgs() const {
  return m_args;
}

} // namespace binding
} // namespace flow_wing