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

#pragma once

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include <vector>
#include <memory>
namespace flow_wing {
namespace binding {

class BoundIndexExpression : public BoundExpression {

public:
  BoundIndexExpression(std::unique_ptr<BoundExpression> left_expression,
                       std::shared_ptr<types::Type> type,
                       std::vector<std::unique_ptr<BoundExpression>>
                           dimension_clause_expressions,
                       const flow_wing::diagnostic::SourceLocation &location);
  ~BoundIndexExpression() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;

  // Getters
  std::shared_ptr<types::Type> getType() const override;

  // Getters
  const std::vector<std::unique_ptr<BoundExpression>> &
  getDimensionClauseExpressions() const;
  const std::unique_ptr<BoundExpression> &getLeftExpression() const;

private:
  std::unique_ptr<BoundExpression> m_left_expression;
  std::shared_ptr<types::Type> m_type;
  std::vector<std::unique_ptr<BoundExpression>> m_dimension_clause_expressions;
};
} // namespace binding
} // namespace flow_wing