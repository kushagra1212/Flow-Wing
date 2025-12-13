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

#include "BoundCompilationUnit.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"

namespace flow_wing {
namespace binding {

BoundCompilationUnit::BoundCompilationUnit(
    std::vector<std::unique_ptr<BoundStatement>> statements,
    const flow_wing::diagnostic::SourceLocation &location,
    std::shared_ptr<analysis::ScopedSymbolTable> symbol_table)
    : BoundNode(location), m_statements(std::move(statements)),
      m_symbol_table(std::move(symbol_table)) {}

BoundCompilationUnit::~BoundCompilationUnit() = default;

NodeKind BoundCompilationUnit::getKind() const {
  return NodeKind::kCompilationUnit;
}

const std::shared_ptr<analysis::ScopedSymbolTable> &
BoundCompilationUnit::getSymbolTable() const {
  return m_symbol_table;
}

void BoundCompilationUnit::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<std::unique_ptr<BoundStatement>> &
BoundCompilationUnit::getStatements() const {
  return m_statements;
}

} // namespace binding
} // namespace flow_wing