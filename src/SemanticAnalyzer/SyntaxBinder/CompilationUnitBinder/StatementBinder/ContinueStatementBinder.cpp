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

#include "StatementBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundContinueStatement/BoundContinueStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement> StatementBinder::bindContinueStatement(
    syntax::ContinueStatementSyntax *statement) {
  assert(statement != nullptr &&
         "ContinueStatementBinder::bind: statement is null");

  auto continue_statement =
      static_cast<syntax::ContinueStatementSyntax *>(statement);

  if (!m_context->getSymbolTable()->isInBreakScope()) {
    auto error_statement = std::make_unique<BoundErrorStatement>(
        continue_statement->getSourceLocation(),
        diagnostic::DiagnosticCode::kContinueStatementNotAllowedOutsideOfLoop,
        diagnostic::DiagnosticArgs{});

    m_context->reportError(error_statement.get());
    return std::move(error_statement);
  }

  return std::make_unique<BoundContinueStatement>(
      continue_statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing