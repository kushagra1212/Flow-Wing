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
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryOperator/BoundBinaryOperator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/BinaryExpressionSyntax/BinaryExpressionSyntax.h"

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> ExpressionBinder::bindBinaryExpression(
    syntax::BinaryExpressionSyntax *expression) {

  auto left_expression_syntax = expression->getLeft().get();
  auto right_expression_syntax = expression->getRight().get();
  auto operator_token = expression->getOperatorToken();

  auto left_expression = bind(left_expression_syntax);

  if (left_expression->getKind() == NodeKind::kErrorExpression) {
    return left_expression;
  }

  auto right_expression = bind(right_expression_syntax);

  if (right_expression->getKind() == NodeKind::kErrorExpression) {
    return right_expression;
  }

  auto binary_operator = BoundBinaryOperator::bind(
      operator_token->getTokenKind(), left_expression->getType(),
      right_expression->getType());

  if (binary_operator == nullptr) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kInvalidBinaryOperationWithTypes,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            lexer::toString(operator_token->getTokenKind()),
            left_expression->getType()->getName(),
            right_expression->getType()->getName()});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  return std::make_unique<BoundBinaryExpression>(
      std::move(left_expression), binary_operator, std::move(right_expression),
      expression->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing