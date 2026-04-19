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
#include "src/SemanticAnalyzer/BoundExpressions/BoundColonExpression/BoundColonExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"

namespace flow_wing {
namespace binding {
std::unique_ptr<BoundExpression> ExpressionBinder::bindColonExpression(
    syntax::ColonExpressionSyntax *expression) {
  auto left_expression = expression->getLeftExpression().get();
  if (left_expression->getKind() != syntax::NodeKind::kIdentifierExpression) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        left_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kUnexpectedExpression,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            syntax::toString(left_expression->getKind()),
            syntax::toString(syntax::NodeKind::kIdentifierExpression)});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto field_name =
      static_cast<syntax::IdentifierExpressionSyntax *>(left_expression)
          ->getValue();

  auto right_expression = bind(expression->getRightExpression().get());
  if (right_expression->getKind() == NodeKind::kErrorExpression) {
    return right_expression;
  }
  return std::make_unique<BoundColonExpression>(
      field_name, std::move(right_expression), expression->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing