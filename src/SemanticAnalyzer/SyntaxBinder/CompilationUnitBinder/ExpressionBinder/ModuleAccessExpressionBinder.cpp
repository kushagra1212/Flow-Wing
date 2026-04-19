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

#include "ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundModuleAccessExpression/BoundModuleAccessExpression.hpp"
#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/ModuleAccessExpressionSyntax/ModuleAccessExpressionSyntax.h"
#include <cassert>
#include <memory>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> ExpressionBinder::bindModuleAccessExpression(
    syntax::ModuleAccessExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "ModuleAccessExpressionBinder::bind: expression is null");

  auto module_name_expression =
      bind(expression->getModuleNameExpression().get());

  if (module_name_expression->getKind() == NodeKind::kErrorExpression) {
    return module_name_expression;
  }

  auto module_name = static_cast<syntax::IdentifierExpressionSyntax *>(
                         expression->getModuleNameExpression().get())
                         ->getValue();

  auto symbol = m_context->getSymbolTable()->lookup(module_name).get();

  if (!symbol) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        expression->getModuleNameExpression()->getSourceLocation(),
        diagnostic::DiagnosticCode::kModuleNotFound,
        diagnostic::DiagnosticArgs{module_name});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto module_symbol = static_cast<analysis::ModuleSymbol *>(symbol);

  auto modules_symbol_table = module_symbol->getModuleSymbolTable();

  auto current_symbol_table = m_context->getSymbolTable();

  m_context->switchSymbolTable(modules_symbol_table);

  auto member_access_expression =
      bind(expression->getMemberAccessExpression().get());

  if (member_access_expression->getKind() == NodeKind::kErrorExpression) {
    m_context->switchSymbolTable(current_symbol_table);
    return member_access_expression;
  }

  m_context->switchSymbolTable(current_symbol_table);

  return std::make_unique<BoundModuleAccessExpression>(
      module_symbol, std::move(member_access_expression),
      expression->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing