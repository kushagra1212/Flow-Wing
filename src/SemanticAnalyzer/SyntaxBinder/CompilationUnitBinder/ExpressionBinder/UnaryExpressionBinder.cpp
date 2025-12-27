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
#include "src/SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/UnaryExpressionSyntax/UnaryExpressionSyntax.h"
namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> ExpressionBinder::bindUnaryExpression(
    syntax::UnaryExpressionSyntax *syntax_node) {

  auto bound_expression = bind(syntax_node->getExpression().get());

  if (bound_expression->getKind() == NodeKind::kErrorExpression) {
    return bound_expression;
  }

  auto operator_token_kind = syntax_node->getOperatorTokenKind();

  const auto &[is_allowed, resolved_type] =
      isUnaryAllowedType(operator_token_kind, bound_expression->getType());

  if (!is_allowed) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        bound_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kInvalidUnaryOperator,
        diagnostic::DiagnosticArgs{lexer::toString(operator_token_kind),
                                   bound_expression->getType()->getName()});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  return std::make_unique<BoundUnaryExpression>(
      operator_token_kind, std::move(bound_expression), resolved_type,
      syntax_node->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing