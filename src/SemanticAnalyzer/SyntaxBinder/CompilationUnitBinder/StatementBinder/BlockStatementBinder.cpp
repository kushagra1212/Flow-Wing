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
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement>
StatementBinder::bindBlockStatement(syntax::BlockStatementSyntax *statement) {
  assert(statement != nullptr &&
         "BlockStatementBinder::bind: statement is null");

  auto block_statement = static_cast<syntax::BlockStatementSyntax *>(statement);

  m_context->getSymbolTable()->enterScope();

  std::vector<std::unique_ptr<BoundStatement>> statements;

  for (const auto &statement : block_statement->getStatements()) {

    auto bound_statement = bind(statement.get());

    if (bound_statement->getKind() == NodeKind::kErrorStatement) {
      return bound_statement;
    }

    statements.push_back(std::move(bound_statement));
  }

  m_context->getSymbolTable()->leaveScope();

  return std::make_unique<BoundBlockStatement>(
      std::move(statements), block_statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing