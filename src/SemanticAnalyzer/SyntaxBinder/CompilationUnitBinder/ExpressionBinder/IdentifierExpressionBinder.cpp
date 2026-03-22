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

#include "ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundMemberAccessExpression/BoundMemberAccessExpression.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/SuperExpressionSyntax/SuperExpressionSyntax.h"
#include "src/utils/LogConfig.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> ExpressionBinder::bindIdentifierExpression(
    syntax::IdentifierExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "IdentifierExpressionBinder::bind: expression is null");

  auto identifier_expression =
      static_cast<syntax::IdentifierExpressionSyntax *>(expression);

  auto identifier = identifier_expression->getValue();

  auto symbol = m_context->getSymbolTable()->lookup(identifier).get();

  auto self_sh = m_context->getSymbolTable()->lookup("self");
  std::shared_ptr<types::ClassType> ct;
  if (self_sh)
    ct = std::dynamic_pointer_cast<types::ClassType>(self_sh->getType());
  if (!ct && m_context->getCurrentClassType())
    ct = std::dynamic_pointer_cast<types::ClassType>(
        m_context->getCurrentClassType());
  if (ct && self_sh) {
    auto field = ct->lookupField(identifier);
    if (field && field->getKind() == analysis::SymbolKind::kVariable) {
      if (!symbol || field.get() == symbol) {
        auto self_expr = std::make_unique<BoundIdentifierExpression>(
            self_sh.get(), expression->getSourceLocation());
        return std::make_unique<BoundMemberAccessExpression>(
            std::move(self_expr), identifier, field->getType(),
            expression->getSourceLocation());
      }
    }
  }

  if (!symbol) {
    BINDER_DEBUG_LOG("Symbol not found", "IDENTIFIER EXPRESSION BINDER");

    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kVariableNotFound,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{identifier});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  return std::make_unique<BoundIdentifierExpression>(
      symbol, expression->getSourceLocation());
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindSuperExpression(
    syntax::SuperExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "SuperExpressionBinder::bind: expression is null");

  auto error_expression = std::make_unique<BoundErrorExpression>(
      expression->getSourceLocation(),
      diagnostic::DiagnosticCode::kVariableNotFound,
      std::vector<flow_wing::diagnostic::DiagnosticArg>{std::string("super")});

  m_context->reportError(error_expression.get());
  return std::move(error_expression);
}
} // namespace binding
} // namespace flow_wing