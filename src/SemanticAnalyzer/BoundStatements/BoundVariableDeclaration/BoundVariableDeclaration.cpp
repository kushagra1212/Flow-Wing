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

#include "BoundVariableDeclaration.h"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"

namespace flow_wing {
namespace binding {

BoundVariableDeclaration::BoundVariableDeclaration(
    std::vector<std::shared_ptr<analysis::Symbol>> symbols,
    std::vector<std::unique_ptr<BoundExpression>> initializer_expressions,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundDeclarationStatement(location), m_symbols(std::move(symbols)),
      m_initializer_expressions(std::move(initializer_expressions)) {}

NodeKind BoundVariableDeclaration::getKind() const {
  return NodeKind::kVariableDeclaration;
}

const std::vector<std::shared_ptr<analysis::Symbol>> &
BoundVariableDeclaration::getSymbols() const {
  return m_symbols;
}

const std::vector<std::unique_ptr<BoundExpression>> &
BoundVariableDeclaration::getInitializerExpressions() const {
  return m_initializer_expressions;
}

void BoundVariableDeclaration::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

} // namespace binding
} // namespace flow_wing