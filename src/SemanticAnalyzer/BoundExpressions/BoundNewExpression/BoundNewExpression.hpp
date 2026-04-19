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

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include <memory>
#include <vector>

namespace flow_wing {
namespace binding {

class BoundNewExpression : public BoundExpression {

public:
  BoundNewExpression(std::unique_ptr<BoundExpression> expression,
                     const flow_wing::diagnostic::SourceLocation &location);
  BoundNewExpression(
      std::unique_ptr<BoundExpression> expression,
      std::vector<std::unique_ptr<BoundExpression>> arguments,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundNewExpression() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  std::shared_ptr<types::Type> getType() const override;

  const std::unique_ptr<BoundExpression> &getExpression() const;
  const std::vector<std::unique_ptr<BoundExpression>> &getArguments() const;

private:
  std::unique_ptr<BoundExpression> m_expression;
  std::vector<std::unique_ptr<BoundExpression>> m_arguments;
};
} // namespace binding
} // namespace flow_wing