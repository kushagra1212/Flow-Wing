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

#include "src/SemanticAnalyzer/BoundStatements/BoundDeclarationStatement.hpp"
#include <memory>
#include <vector>
namespace flow_wing {
namespace analysis {
class VariableSymbol;
} // namespace analysis
namespace binding {

class BoundExpression;

class BoundVariableDeclaration : public BoundDeclarationStatement {

public:
  BoundVariableDeclaration(
      std::vector<std::shared_ptr<analysis::Symbol>> symbols,
      std::vector<std::unique_ptr<BoundExpression>> initializer_expressions,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundVariableDeclaration() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  // Getters
  const std::vector<std::shared_ptr<analysis::Symbol>> &
  getSymbols() const override;

  const std::vector<std::unique_ptr<BoundExpression>> &
  getInitializerExpressions() const;

private:
  std::vector<std::shared_ptr<analysis::Symbol>> m_symbols;
  std::vector<std::unique_ptr<BoundExpression>> m_initializer_expressions;
};
} // namespace binding
} // namespace flow_wing