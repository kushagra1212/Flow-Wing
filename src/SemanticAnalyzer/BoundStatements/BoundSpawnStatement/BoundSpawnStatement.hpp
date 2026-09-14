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

#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include <memory>

namespace flow_wing {
namespace binding {

// `spawn f()` — the call is queued on the scheduler instead of performed here.
// The binder guarantees the operand really is a call, so IRGen can go straight
// to the callee's FunctionSymbol without re-checking.
class BoundSpawnStatement : public BoundStatement {

public:
  BoundSpawnStatement(std::unique_ptr<BoundCallExpression> call_expression,
                      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundSpawnStatement() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;

  // Getters
  const std::unique_ptr<BoundCallExpression> &getCallExpression() const;

private:
  std::unique_ptr<BoundCallExpression> m_call_expression;
};
} // namespace binding
} // namespace flow_wing
