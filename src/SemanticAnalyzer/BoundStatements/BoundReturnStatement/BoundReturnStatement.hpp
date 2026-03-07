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
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include <vector>

namespace flow_wing {
namespace binding {

class BoundReturnStatement : public BoundStatement {

public:
  BoundReturnStatement(
      std::vector<std::unique_ptr<BoundExpression>> return_expressions,
      const analysis::FunctionSymbol *function_symbol,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundReturnStatement() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  // Getters
  const std::vector<std::unique_ptr<BoundExpression>> &
  getReturnExpressions() const;
  const analysis::FunctionSymbol *getFunctionSymbol() const;

private:
  std::vector<std::unique_ptr<BoundExpression>> m_return_expressions;
  const analysis::FunctionSymbol *m_function_symbol;
};
} // namespace binding
} // namespace flow_wing