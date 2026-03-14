/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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

#include "BoundIfStatement.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"

namespace flow_wing {
namespace binding {

BoundIfStatement::BoundIfStatement(
    std::unique_ptr<BoundExpression> if_condition,
    std::unique_ptr<BoundStatement> if_statement,
    std::vector<std::unique_ptr<BoundExpression>> or_if_conditions,
    std::vector<std::unique_ptr<BoundStatement>> or_if_statements,
    std::unique_ptr<BoundStatement> else_clause,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundStatement(location), m_if_condition(std::move(if_condition)),
      m_if_statement(std::move(if_statement)),
      m_or_if_conditions(std::move(or_if_conditions)),
      m_or_if_statements(std::move(or_if_statements)),
      m_else_clause(std::move(else_clause)) {}

NodeKind BoundIfStatement::getKind() const { return NodeKind::kIfStatement; }

const std::unique_ptr<BoundExpression> &
BoundIfStatement::getIfCondition() const {
  return m_if_condition;
}
const std::unique_ptr<BoundStatement> &
BoundIfStatement::getIfStatement() const {
  return m_if_statement;
}
const std::vector<std::unique_ptr<BoundExpression>> &
BoundIfStatement::getOrIfConditions() const {
  return m_or_if_conditions;
}
const std::vector<std::unique_ptr<BoundStatement>> &
BoundIfStatement::getOrIfStatements() const {
  return m_or_if_statements;
}
const std::unique_ptr<BoundStatement> &BoundIfStatement::getElseClause() const {
  return m_else_clause;
}
void BoundIfStatement::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

} // namespace binding
} // namespace flow_wing