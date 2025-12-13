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

#include "BoundCustomTypeStatement.h"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundDeclarationStatement.hpp"
#include "src/common/Symbol/Symbol.hpp"

namespace flow_wing {
namespace binding {

BoundCustomTypeStatement::BoundCustomTypeStatement(
    std::vector<std::shared_ptr<analysis::Symbol>> symbols,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundDeclarationStatement(location), m_symbols(symbols) {}

NodeKind BoundCustomTypeStatement::getKind() const {
  return NodeKind::kCustomTypeStatement;
}

void BoundCustomTypeStatement::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<std::shared_ptr<analysis::Symbol>> &
BoundCustomTypeStatement::getSymbols() const {
  return m_symbols;
}

} // namespace binding
} // namespace flow_wing