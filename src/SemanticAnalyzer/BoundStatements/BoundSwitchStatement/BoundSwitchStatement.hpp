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

class BoundSwitchStatement : public BoundStatement {

public:
  BoundSwitchStatement(
      std::unique_ptr<BoundExpression> switch_condition_expression,
      std::unique_ptr<BoundStatement> default_case_statement,
      std::vector<std::unique_ptr<BoundExpression>> case_expressions,
      std::vector<std::unique_ptr<BoundStatement>> case_statements,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundSwitchStatement() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;

  // Getters
  const std::unique_ptr<BoundExpression> &getSwitchConditionExpression() const;
  const std::unique_ptr<BoundStatement> &getDefaultCaseStatement() const;
  const std::vector<std::unique_ptr<BoundExpression>> &getCaseExpressions() const;
  const std::vector<std::unique_ptr<BoundStatement>> &getCaseStatements() const;

private:
  std::unique_ptr<BoundExpression> m_switch_condition_expression;
  std::unique_ptr<BoundStatement> m_default_case_statement;
  std::vector<std::unique_ptr<BoundExpression>> m_case_expressions;
  std::vector<std::unique_ptr<BoundStatement>> m_case_statements;
};
} // namespace binding
} // namespace flow_wing