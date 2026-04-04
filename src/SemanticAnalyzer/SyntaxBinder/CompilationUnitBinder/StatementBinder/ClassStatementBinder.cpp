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

#include "StatementBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundClassStatement/BoundClassStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundDeclarationStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/TypeResolver/TypeResolver.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ParameterSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/syntax/expression/FunctionReturnTypeExpressionSyntax/FunctionReturnTypeExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "src/syntax/statements/FunctionStatementSyntax/FunctionStatementSyntax.h"
#include "src/syntax/statements/ParameterExpressionSyntax/ParameterExpressionSyntax.h"
#include <cassert>
#include <utility>

namespace flow_wing {
namespace binding {

namespace {

std::string mangleVisibleParamTypes(
    const std::vector<std::shared_ptr<types::ParameterType>> &params) {
  std::string s;
  for (size_t i = 0; i < params.size(); i++) {
    if (i)
      s += "_";
    s += params[i]->type ? params[i]->type->getName() : std::string("?");
  }
  if (s.empty())
    s = "void";
  return s;
}

} // namespace

std::unique_ptr<BoundStatement>
StatementBinder::bindClassStatement(syntax::ClassStatementSyntax *statement) {
  assert(statement != nullptr &&
         "ClassStatementBinder::bind: statement is null");

  auto class_statement = static_cast<syntax::ClassStatementSyntax *>(statement);

  auto class_name = static_cast<syntax::IdentifierExpressionSyntax *>(
                        class_statement->getClassNameIdentifierExpr().get())
                        ->getValue();

  if (m_context->isDuplicateClassDeclaration(class_name)) {
    auto error_statement = std::make_unique<BoundErrorStatement>(
        class_statement->getClassNameIdentifierExpr()->getSourceLocation(),
        diagnostic::DiagnosticCode::kClassAlreadyDeclared,
        diagnostic::DiagnosticArgs{class_name});
    m_context->reportError(error_statement.get());
    return std::move(error_statement);
  }

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

  auto parent_class_type =
      std::dynamic_pointer_cast<types::ClassType>(parent_class_type_base);

  std::shared_ptr<types::ClassType> class_type;
  auto existing_class_symbol = m_context->getSymbolTable()->lookup(class_name);
  if (existing_class_symbol &&
      existing_class_symbol->getKind() == analysis::SymbolKind::kClass) {
    class_type = std::dynamic_pointer_cast<types::ClassType>(
        existing_class_symbol->getType());
  }
  if (!class_type) {
    class_type =
        std::make_shared<types::ClassType>(class_name, parent_class_type);
  }

  m_context->getSymbolTable()->enterScope();

  for (const auto &class_member_statement_syntax :
       class_statement->getClassMemberStatements()) {
    if (class_member_statement_syntax->getKind() !=
        syntax::NodeKind::kFunctionStatement) {
      continue;
    }
    auto *func_syntax = static_cast<syntax::FunctionStatementSyntax *>(
        class_member_statement_syntax.get());
    auto function_identifier =
        static_cast<syntax::IdentifierExpressionSyntax *>(
            func_syntax->getIdentifier().get());
    const auto &function_name = function_identifier->getValue();

    std::vector<std::shared_ptr<types::ParameterType>> params;
    size_t default_value_start_index = static_cast<size_t>(-1), count = 0;
    for (auto &param : func_syntax->getParameters()) {
      auto *param_expr =
          static_cast<syntax::ParameterExpressionSyntax *>(param.get());
      params.push_back(
          m_context->getTypeResolver()->resolveParameterExpression(param_expr));
      if (param_expr->hasDefaultValueExpression() &&
          default_value_start_index == static_cast<size_t>(-1)) {
        default_value_start_index = count;
      }
      count++;
    }
    const auto visible_for_mangle = params;
    params.push_back(std::make_shared<types::ParameterType>(class_type));

    std::vector<std::shared_ptr<types::ReturnType>> return_types;
    if (func_syntax->hasReturnType()) {
      auto result = m_context->getTypeResolver()->resolveReturnType(
          static_cast<syntax::FunctionReturnTypeExpressionSyntax *>(
              func_syntax->getReturnType().get()));
      if (result.second != nullptr) {
        m_context->reportError(result.second.get());
        return std::make_unique<BoundErrorStatement>(std::move(result.second));
      }
      return_types = result.first;
    } else {
      auto inferred =
          m_context->getTypeResolver()->inferImplicitReturnTypeFromBody(
              static_cast<syntax::BlockStatementSyntax *>(
                  func_syntax->getBody().get()));
      if (inferred && !inferred->isNthg()) {
        return_types.push_back(std::make_shared<types::ReturnType>(inferred));
      } else {
        return_types.push_back(std::make_shared<types::ReturnType>(
            analysis::Builtins::m_nthg_type_instance));
      }
    }

    auto function_type = std::make_shared<types::FunctionType>(
        std::move(params), std::move(return_types), default_value_start_index,
        false);
    auto function_symbol = std::make_shared<analysis::FunctionSymbol>(
        function_name, std::move(function_type));
    function_symbol->setMangledName(
        class_name + "." + function_name + "." +
        mangleVisibleParamTypes(visible_for_mangle));
    function_symbol->setDeclarationSite(
        m_context->getCompilationContext().getAbsoluteSourceFilePath(),
        function_identifier->getSourceLocation());
    if (!class_type->defineMember(function_symbol)) {
      auto error_statement = std::make_unique<BoundErrorStatement>(
          func_syntax->getSourceLocation(),
          diagnostic::DiagnosticCode::kFunctionAlreadyDeclared,
          diagnostic::DiagnosticArgs{function_name});
      m_context->reportError(error_statement.get());
      m_context->getSymbolTable()->leaveScope();
      return std::move(error_statement);
    }
  }

  m_context->setCurrentClassType(class_type);

  std::vector<std::shared_ptr<analysis::Symbol>> class_member_symbols;
  std::vector<std::unique_ptr<BoundStatement>> class_member_statements;

  // Pass 1: bind variable declarations and custom type statements so that
  // the ClassType's member list is populated before function bodies are bound.
  // This allows self.member access inside method bodies to resolve correctly.
  for (const auto &class_member_statement_syntax :
       class_statement->getClassMemberStatements()) {

    switch (class_member_statement_syntax->getKind()) {
    case syntax::NodeKind::kCustomTypeStatement:
    case syntax::NodeKind::kVariableDeclaration: {

      auto bound_statement = bind(class_member_statement_syntax.get());

      if (bound_statement->getKind() == NodeKind::kErrorStatement) {
        m_context->setCurrentClassType(nullptr);
        m_context->getSymbolTable()->leaveScope();
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
    case syntax::NodeKind::kFunctionStatement:
      break;

    default:
      m_context->setCurrentClassType(nullptr);
      m_context->getSymbolTable()->leaveScope();
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

  // Populate the ClassType with variable/type members before binding functions
  // so that self.member access works inside method bodies.
  for (const auto &symbol : class_member_symbols) {
    if (!class_type->defineMember(symbol)) {

      auto error_statement = std::make_unique<BoundErrorStatement>(
          class_statement->getSourceLocation(),
          diagnostic::DiagnosticCode::kDuplicateMemberInClass,
          diagnostic::DiagnosticArgs{symbol->getName(), class_name});

      m_context->reportError(error_statement.get());
      m_context->getSymbolTable()->leaveScope();
      return std::move(error_statement);
    }
  }

  // Pass 2: bind function statements. Their bodies can now resolve
  // self.member because the ClassType already has all field AND function
  // members.
  for (const auto &class_member_statement_syntax :
       class_statement->getClassMemberStatements()) {

    if (class_member_statement_syntax->getKind() !=
        syntax::NodeKind::kFunctionStatement) {
      continue;
    }

    auto bound_statement = bind(class_member_statement_syntax.get());

    if (bound_statement->getKind() == NodeKind::kErrorStatement) {
      m_context->setCurrentClassType(nullptr);
      m_context->getSymbolTable()->leaveScope();
      return bound_statement;
    }

    auto bound_declaration_statement =
        static_cast<BoundDeclarationStatement *>(bound_statement.get());

    auto symbols = bound_declaration_statement->getSymbols();

    for (const auto &symbol : symbols) {
      class_member_symbols.push_back(symbol);
    }

    class_member_statements.push_back(std::move(bound_statement));
  }

  m_context->setCurrentClassType(nullptr);

  // Function members were already pre-defined on the ClassType before pass 2.
  // No need to re-define them here.

  // If the class was already pre-declared by the DeclarationAnalyzer, reuse
  // that symbol (the ClassType is already the same shared instance).
  // Otherwise define it now.
  std::shared_ptr<analysis::Symbol> class_symbol;
  if (existing_class_symbol) {
    class_symbol = existing_class_symbol;
  } else {
    class_symbol = std::make_shared<analysis::Symbol>(
        class_name, analysis::SymbolKind::kClass, class_type);
    class_symbol->setDeclarationSite(
        m_context->getCompilationContext().getAbsoluteSourceFilePath(),
        static_cast<syntax::IdentifierExpressionSyntax *>(
            class_statement->getClassNameIdentifierExpr().get())
            ->getSourceLocation());
    if (!m_context->getSymbolTable()->defineInEnclosingScope(class_symbol)) {
      auto error_statement = std::make_unique<BoundErrorStatement>(
          class_statement->getSourceLocation(),
          diagnostic::DiagnosticCode::kClassAlreadyDeclared,
          diagnostic::DiagnosticArgs{class_name});
      m_context->reportError(error_statement.get());
      m_context->getSymbolTable()->leaveScope();
      return std::move(error_statement);
    }
  }

  m_context->getSymbolTable()->leaveScope();

  return std::make_unique<BoundClassStatement>(
      class_symbol, std::move(class_member_statements),
      class_statement->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing