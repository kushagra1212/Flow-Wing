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



#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/DeclarationAnalyzer/DeclarationAnalyzer.hpp"
#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"

namespace flow_wing {
void analysis::DeclarationAnalyzer::visit(syntax::ModuleStatementSyntax *node) {
  auto *name_expr = static_cast<syntax::IdentifierExpressionSyntax *>(
      node->getModuleNameExpression().get());
  const std::string &module_name = name_expr->getValue();

  auto module_table = std::make_shared<analysis::ScopedSymbolTable>();
  analysis::Builtins::registerIntoSymbolTable(module_table);

  auto module_symbol =
      std::make_shared<analysis::ModuleSymbol>(module_name, module_table);

  if (!m_binder_context.getSymbolTable()->define(module_symbol)) {
    m_binder_context.reportError(
        flow_wing::diagnostic::DiagnosticCode::kModuleAlreadyDeclared,
        {module_name}, name_expr->getSourceLocation());
    return;
  }

  if (!module_table->define(module_symbol)) {
    m_binder_context.reportError(
        flow_wing::diagnostic::DiagnosticCode::kModuleAlreadyDeclared,
        {module_name}, name_expr->getSourceLocation());
    return;
  }

  auto saved = m_binder_context.getSymbolTable();
  m_binder_context.switchSymbolTable(module_table);
  m_binder_context.pushModuleScope(module_name);
  for (const auto &stmt : node->getModuleMemberStatements()) {
    stmt->accept(this);
  }
  m_binder_context.popModuleScope();
  m_binder_context.switchSymbolTable(saved);
}
} // namespace flow_wing