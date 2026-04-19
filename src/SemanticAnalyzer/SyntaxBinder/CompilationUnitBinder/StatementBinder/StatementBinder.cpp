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
#include "src/SemanticAnalyzer/BoundStatements/BoundModuleStatement/BoundModuleStatement.hpp"
#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/BringStatementSyntax/BringStatementSyntax.h"
#include "src/syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "src/syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/syntax/statements/ExposeStatementSyntax/ExposeStatementSyntax.h"
#include "src/syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.hpp"
#include "src/syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "src/syntax/statements/FunctionStatementSyntax/FunctionStatementSyntax.h"
#include "src/syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "src/syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"
#include "src/syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include "src/syntax/statements/SwitchStatementSyntax/SwitchStatementSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "src/syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include "src/utils/LogConfig.h"

namespace flow_wing {
namespace binding {

StatementBinder::StatementBinder(BinderContext *context,
                                 ExpressionBinder *expression_binder)
    : m_context(context), m_expression_binder(expression_binder) {}

std::unique_ptr<BoundStatement>
StatementBinder::bind(syntax::StatementSyntax *statement) {
  switch (statement->getKind()) {
  case syntax::NodeKind::kBlockStatement:
    return bindBlockStatement(
        static_cast<syntax::BlockStatementSyntax *>(statement));
  case syntax::NodeKind::kFunctionStatement:
    return bindFunctionStatement(
        static_cast<syntax::FunctionStatementSyntax *>(statement));
  case syntax::NodeKind::kCustomTypeStatement:
    return bindCustomTypeStatement(
        static_cast<syntax::CustomTypeStatementSyntax *>(statement));
  case syntax::NodeKind::kVariableDeclaration:
    return bindVariableDeclaration(
        static_cast<syntax::VariableDeclarationSyntax *>(statement));
  case syntax::NodeKind::kExposeStatement:
    return bindExposeStatement(
        static_cast<syntax::ExposeStatementSyntax *>(statement));
  case syntax::NodeKind::kIfStatement:
    return bindIfStatement(static_cast<syntax::IfStatementSyntax *>(statement));
  case syntax::NodeKind::kWhileStatement:
    return bindWhileStatement(
        static_cast<syntax::WhileStatementSyntax *>(statement));
  case syntax::NodeKind::kForStatement:
    return bindForStatement(
        static_cast<syntax::ForStatementSyntax *>(statement));
  case syntax::NodeKind::kBreakStatement:
    return bindBreakStatement(
        static_cast<syntax::BreakStatementSyntax *>(statement));
  case syntax::NodeKind::kContinueStatement:
    return bindContinueStatement(
        static_cast<syntax::ContinueStatementSyntax *>(statement));
  case syntax::NodeKind::kReturnStatement:
    return bindReturnStatement(
        static_cast<syntax::ReturnStatementSyntax *>(statement));
  case syntax::NodeKind::kSwitchStatement:
    return bindSwitchStatement(
        static_cast<syntax::SwitchStatementSyntax *>(statement));
  case syntax::NodeKind::kClassStatement:
    return bindClassStatement(
        static_cast<syntax::ClassStatementSyntax *>(statement));
  case syntax::NodeKind::kBringStatement:
    return bindBringStatement(
        static_cast<syntax::BringStatementSyntax *>(statement));
  case syntax::NodeKind::kModuleStatement:
    return bindModuleStatement(
        static_cast<syntax::ModuleStatementSyntax *>(statement));

  default:
    return bindExpressionStatement(
        static_cast<syntax::ExpressionStatementSyntax *>(statement));
  }
}

std::unique_ptr<BoundStatement>
StatementBinder::bindBringStatement(syntax::BringStatementSyntax *statement) {
  (void)statement;
  // DeclarationAnalyzer already validates the brought file; no IR for bring.
  return std::make_unique<BoundBlockStatement>(
      std::vector<std::unique_ptr<BoundStatement>>{},
      statement->getStringLiteralExpression()->getSourceLocation());
}

std::unique_ptr<BoundStatement>
StatementBinder::bindModuleStatement(syntax::ModuleStatementSyntax *statement) {
  auto *name_expr = static_cast<syntax::IdentifierExpressionSyntax *>(
      statement->getModuleNameExpression().get());
  std::shared_ptr<analysis::Symbol> sym =
      m_context->getSymbolTable()->lookup(name_expr->getValue());
  if (!sym || sym->getKind() != analysis::SymbolKind::kModule) {
    return std::make_unique<BoundModuleStatement>(
        std::vector<std::unique_ptr<BoundStatement>>{},
        name_expr->getSourceLocation());
  }

  auto *module_symbol = static_cast<analysis::ModuleSymbol *>(sym.get());
  auto module_table = module_symbol->getModuleSymbolTable();
  auto saved = m_context->getSymbolTable();
  m_context->switchSymbolTable(module_table);

  std::vector<std::unique_ptr<BoundStatement>> inner;
  for (const auto &st : statement->getModuleMemberStatements()) {
    inner.push_back(bind(st.get()));
  }
  m_context->switchSymbolTable(saved);

  return std::make_unique<BoundModuleStatement>(
      std::move(inner), name_expr->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing