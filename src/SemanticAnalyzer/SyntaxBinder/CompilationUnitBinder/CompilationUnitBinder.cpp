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

#include "CompilationUnitBinder.hpp"
#include "ExpressionBinder/ExpressionBinder.hpp"
#include "StatementBinder/StatementBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/SemanticAnalyzer/TypeResolver/TypeResolver.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/syntax/CompilationUnitSyntax.h"

namespace flow_wing {
namespace binding {

CompilationUnitBinder::CompilationUnitBinder(BinderContext *context)
    : m_context(context), m_symbol_table(context->getSymbolTable()) {}

std::shared_ptr<analysis::ScopedSymbolTable>
CompilationUnitBinder::getSymbolTable() const {
  return m_symbol_table;
}

std::unique_ptr<BoundCompilationUnit>
CompilationUnitBinder::bind(syntax::CompilationUnitSyntax *syntax) {

  auto expression_binder = std::make_unique<ExpressionBinder>(m_context);
  auto statement_binder =
      std::make_unique<StatementBinder>(m_context, expression_binder.get());

  std::vector<std::unique_ptr<BoundStatement>> statements;

  for (const auto &statement : syntax->getStatements()) {
    statements.push_back(statement_binder->bind(statement.get()));
  }

  return std::make_unique<BoundCompilationUnit>(std::move(statements),
                                                syntax->getSourceLocation(),
                                                std::move(m_symbol_table));
}

} // namespace binding
} // namespace flow_wing