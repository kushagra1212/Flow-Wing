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
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
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
} // namespace binding
} // namespace flow_wing