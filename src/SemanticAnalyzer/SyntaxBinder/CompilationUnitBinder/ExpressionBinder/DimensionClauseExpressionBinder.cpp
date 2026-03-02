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
#include "src/SemanticAnalyzer/BoundExpressions/BoundDimensionClauseExpression/BoundDimensionClauseExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/DimensionClauseExpressionSyntax/DimensionClauseExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"

namespace flow_wing {
namespace binding {
std::unique_ptr<BoundExpression>
ExpressionBinder::bindDimensionClauseExpression(
    syntax::DimensionClauseExpressionSyntax *expression) {
  auto size_literal = expression->getSizeLiteral().get();
  auto bound_size_literal = bind(size_literal);
  if (bound_size_literal->getKind() == NodeKind::kErrorExpression) {
    return bound_size_literal;
  }

  auto type = bound_size_literal->getType();

  if ((!type->isDynamic() && !type->isInteger())) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        size_literal->getSourceLocation(),
        diagnostic::DiagnosticCode::kExpectedAnIntegerForIndexing,
        diagnostic::DiagnosticArgs{type->getName()});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  return std::make_unique<BoundDimensionClauseExpression>(
      std::move(bound_size_literal), expression->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing