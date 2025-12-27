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
#include "src/SemanticAnalyzer/BoundStatements/BoundClassStatement/BoundClassStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundDeclarationStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/Type.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include <cassert>
#include <utility>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement>
StatementBinder::bindClassStatement(syntax::ClassStatementSyntax *statement) {
  assert(statement != nullptr &&
         "ClassStatementBinder::bind: statement is null");

  auto class_statement = static_cast<syntax::ClassStatementSyntax *>(statement);

  auto class_name = static_cast<syntax::IdentifierExpressionSyntax *>(
                        class_statement->getClassNameIdentifierExpr().get())
                        ->getValue();

  std::shared_ptr<types::Type> parent_class_type_base = nullptr;

  if (class_statement->getParentClassIdentifierExpr()) {
    auto &parent_class_name =
        static_cast<syntax::IdentifierExpressionSyntax *>(
            class_statement->getParentClassIdentifierExpr().get())
            ->getValue();

    auto parent_class_symbol =
        m_context->getSymbolTable()->lookup(parent_class_name);

    if (parent_class_symbol == nullptr) {

      auto error_statement = std::make_unique<BoundErrorStatement>(
          class_statement->getSourceLocation(),
          diagnostic::DiagnosticCode::kParentClassNotFound,
          diagnostic::DiagnosticArgs{parent_class_name, class_name});

      m_context->reportError(error_statement.get());
      return std::move(error_statement);
    }

    if (parent_class_symbol->getKind() != analysis::SymbolKind::kClass) {
      auto error_statement = std::make_unique<BoundErrorStatement>(
          class_statement->getSourceLocation(),
          diagnostic::DiagnosticCode::kParentClassIsNotAClass,
          diagnostic::DiagnosticArgs{parent_class_name, class_name});

      m_context->reportError(error_statement.get());
      return std::move(error_statement);
    }

    parent_class_type_base = parent_class_symbol->getType();
  }

  m_context->getSymbolTable()->enterScope();

  std::vector<std::shared_ptr<analysis::Symbol>> class_member_symbols;

  std::vector<std::unique_ptr<BoundStatement>> class_member_statements;

  for (const auto &class_member_statement_syntax :
       class_statement->getClassMemberStatements()) {

    switch (class_member_statement_syntax->getKind()) {
    case syntax::NodeKind::kCustomTypeStatement:
    case syntax::NodeKind::kFunctionStatement:
    case syntax::NodeKind::kVariableDeclaration: {

      auto bound_statement = bind(class_member_statement_syntax.get());

      if (bound_statement->getKind() == NodeKind::kErrorStatement) {
        return bound_statement;
      }

      auto bound_declaration_statement =
          static_cast<BoundDeclarationStatement *>(bound_statement.get());

      auto symbols = bound_declaration_statement->getSymbols();

      for (const auto &symbol : symbols) {
        class_member_symbols.push_back(symbol);
      }

      class_member_statements.push_back(std::move(bound_statement));

      break;
    }

    default:
      auto error_statement = std::make_unique<BoundErrorStatement>(
          class_member_statement_syntax->getSourceLocation(),
          diagnostic::DiagnosticCode::kInvalidClassMemberStatement,
          diagnostic::DiagnosticArgs{
              syntax::toString(class_member_statement_syntax->getKind()),
              class_name});

      m_context->reportError(error_statement.get());
      return std::move(error_statement);
    }
  }

  m_context->getSymbolTable()->leaveScope();

  auto parent_class_type =
      std::dynamic_pointer_cast<types::ClassType>(parent_class_type_base);

  auto class_type =
      std::make_shared<types::ClassType>(class_name, parent_class_type);

  for (const auto &symbol : class_member_symbols) {
    if (!class_type->defineMember(symbol)) {

      auto error_statement = std::make_unique<BoundErrorStatement>(
          class_statement->getSourceLocation(),
          diagnostic::DiagnosticCode::kDuplicateMemberInClass,
          diagnostic::DiagnosticArgs{symbol->getName(), class_name});

      m_context->reportError(error_statement.get());
      return std::move(error_statement);
    }
  }

  auto class_symbol = std::make_shared<analysis::Symbol>(
      class_name, analysis::SymbolKind::kClass, class_type);

  if (!m_context->getSymbolTable()->define(class_symbol)) {

    auto error_statement = std::make_unique<BoundErrorStatement>(
        class_statement->getSourceLocation(),
        diagnostic::DiagnosticCode::kClassAlreadyDeclared,
        diagnostic::DiagnosticArgs{class_name});

    m_context->reportError(error_statement.get());
    return std::move(error_statement);
  }

  return std::make_unique<BoundClassStatement>(
      class_symbol, std::move(class_member_statements),
      class_statement->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing