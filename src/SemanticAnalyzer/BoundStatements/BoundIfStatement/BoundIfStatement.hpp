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

#pragma once

#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include <vector>
#include <memory>
namespace flow_wing {
namespace binding {

class BoundExpression;

class BoundIfStatement : public BoundStatement {

public:
  BoundIfStatement(
      std::unique_ptr<BoundExpression> if_condition,
      std::unique_ptr<BoundStatement> if_statement,
      std::vector<std::unique_ptr<BoundExpression>> or_if_conditions,
      std::vector<std::unique_ptr<BoundStatement>> or_if_statements,
      std::unique_ptr<BoundStatement> else_clause,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundIfStatement() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  // Getters

private:
  std::unique_ptr<BoundExpression> m_if_condition;
  std::unique_ptr<BoundStatement> m_if_statement;
  std::vector<std::unique_ptr<BoundExpression>> m_or_if_conditions;
  std::vector<std::unique_ptr<BoundStatement>> m_or_if_statements;
  std::unique_ptr<BoundStatement> m_else_clause;
};
} // namespace binding
} // namespace flow_wing