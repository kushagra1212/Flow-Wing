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

#include "BoundSwitchStatement.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
namespace flow_wing {
namespace binding {

BoundSwitchStatement::BoundSwitchStatement(
    std::unique_ptr<BoundExpression> switch_condition_expression,
    std::unique_ptr<BoundStatement> default_case_statement,
    std::vector<std::unique_ptr<BoundExpression>> case_expressions,
    std::vector<std::unique_ptr<BoundStatement>> case_statements,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundStatement(location),
      m_switch_condition_expression(std::move(switch_condition_expression)),
      m_default_case_statement(std::move(default_case_statement)),
      m_case_expressions(std::move(case_expressions)),
      m_case_statements(std::move(case_statements)) {}

void BoundSwitchStatement::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

NodeKind BoundSwitchStatement::getKind() const {
  return NodeKind::kSwitchStatement;
}

} // namespace binding
} // namespace flow_wing