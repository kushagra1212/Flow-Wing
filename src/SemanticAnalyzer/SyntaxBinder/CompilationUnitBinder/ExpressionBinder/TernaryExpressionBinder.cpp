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
#include "src/SemanticAnalyzer/BoundExpressions/BoundTernaryExpression/BoundTernaryExpression.h"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/TernaryExpressionSyntax/TernaryExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> ExpressionBinder::bindTernaryExpression(
    syntax::TernaryExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "TernaryExpressionBinder::bindTernaryExpression: expression is null");

  auto condition_expression = bind(expression->getConditionExpression().get());

  if (condition_expression->getKind() == NodeKind::kErrorExpression) {
    return condition_expression;
  }

  auto true_expression = bind(expression->getTrueExpression().get());

  if (true_expression->getKind() == NodeKind::kErrorExpression) {
    return true_expression;
  }

  auto false_expression = bind(expression->getFalseExpression().get());

  if (false_expression->getKind() == NodeKind::kErrorExpression) {
    return false_expression;
  }

  if (true_expression->getType() != false_expression->getType()) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kIncompatibleTypesForTernaryExpression,
        diagnostic::DiagnosticArgs{true_expression->getType()->getName(),
                                   false_expression->getType()->getName()});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  return std::make_unique<BoundTernaryExpression>(
      std::move(condition_expression), std::move(true_expression),
      std::move(false_expression), expression->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing