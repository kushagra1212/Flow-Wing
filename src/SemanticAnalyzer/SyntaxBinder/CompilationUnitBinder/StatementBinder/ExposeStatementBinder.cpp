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
#include "src/SemanticAnalyzer/BoundStatements/BoundDeclarationStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundExposeStatement/BoundExposeStatement.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/common/Symbol/Symbol.hpp"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/statements/ExposeStatementSyntax/ExposeStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement>
StatementBinder::bindExposeStatement(syntax::ExposeStatementSyntax *statement) {
  assert(statement != nullptr &&
         "ExposeStatementBinder::bind: statement is null");

  auto expose_statement =
      static_cast<syntax::ExposeStatementSyntax *>(statement);

  auto statement_kind = expose_statement->getStatement()->getKind();

  switch (statement_kind) {
  case syntax::NodeKind::kFunctionStatement:
  case syntax::NodeKind::kClassStatement:
  case syntax::NodeKind::kVariableDeclaration:
  case syntax::NodeKind::kCustomTypeStatement: {
    auto bound_statement = bind(expose_statement->getStatement().get());

    if (bound_statement->getKind() == NodeKind::kErrorStatement) {
      return bound_statement;
    }

    auto bound_declaration_statement =
        static_cast<BoundDeclarationStatement *>(bound_statement.get());

    for (auto &symbol : bound_declaration_statement->getSymbols()) {
      assert(symbol != nullptr &&
             "ExposeStatementBinder::bind: symbol is null");

      symbol->setIsExposed(true);
    }

    return std::make_unique<BoundExposeStatement>(
        std::move(bound_statement), expose_statement->getSourceLocation());
  }
  default: {
    m_context->reportError(flow_wing::diagnostic::DiagnosticCode::
                               kUnsupportedStatementInExposeStatement,
                           {syntax::toString(statement_kind)},
                           expose_statement->getSourceLocation());

    return std::make_unique<BoundErrorStatement>(
        expose_statement->getSourceLocation());
  }
  }
}

} // namespace binding
} // namespace flow_wing