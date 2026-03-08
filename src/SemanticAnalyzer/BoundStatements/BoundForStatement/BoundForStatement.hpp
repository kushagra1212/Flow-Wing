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

class BoundForStatement : public BoundStatement {

public:
  BoundForStatement(std::unique_ptr<BoundStatement> variable_declaration,
                    std::unique_ptr<BoundExpression> assignment_expression,
                    std::unique_ptr<BoundExpression> upper_bound,
                    std::unique_ptr<BoundExpression> step,
                    std::unique_ptr<BoundStatement> body,
                    const flow_wing::diagnostic::SourceLocation &location);
  ~BoundForStatement() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  // Getters

private:
  std::unique_ptr<BoundStatement> m_variable_declaration;
  std::unique_ptr<BoundExpression> m_assignment_expression;
  std::unique_ptr<BoundExpression> m_upper_bound;
  std::unique_ptr<BoundExpression> m_step;
  std::unique_ptr<BoundStatement> m_body;
};
} // namespace binding
} // namespace flow_wing