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
#include "src/SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/ArrayType/ArrayType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> ExpressionBinder::bindIndexExpression(
    syntax::IndexExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "IndexExpressionBinder::bindIndexExpression: expression is null");

  auto left_expression = expression->getLeftExpression().get();

  auto bound_expression = bind(left_expression);

  if (bound_expression->getKind() == NodeKind::kErrorExpression) {
    return bound_expression;
  }

  if (bound_expression->isMultipleType()) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        left_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kIndexingNonArrayTypeVariable,
        diagnostic::DiagnosticArgs{bound_expression->getType()->getName()});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto type = bound_expression->getType();

  std::vector<std::unique_ptr<BoundExpression>> bound_index_expressions;

  if (type->getKind() != types::TypeKind::kArray) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        left_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kIndexingNonArrayTypeVariable,
        diagnostic::DiagnosticArgs{bound_expression->getType()->getName()});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto array_type = static_cast<types::ArrayType *>(type.get());

  for (const auto &dimension_clause_expression :
       expression->getDimensionClauseExpressions()) {
    auto bound_dimension_clause_expression =
        bind(dimension_clause_expression.get());

    if (bound_dimension_clause_expression->getKind() ==
        NodeKind::kErrorExpression) {
      return bound_dimension_clause_expression;
    }

    bound_index_expressions.push_back(
        std::move(bound_dimension_clause_expression));
  }

  std::vector<size_t> inner_type_dimensions(array_type->getDimensions().size() -
                                                bound_index_expressions.size(),
                                            static_cast<size_t>(-1));

  auto inner_type = std::make_shared<types::ArrayType>(
      array_type->getUnderlyingType(), inner_type_dimensions);

  /*
  var x:int[5]
  var y:int[2][3]

  x = y[1] /; here y[1] is of type int[3] and x is of type int[5] both are of
  same underlying type int and have same dimensions

  we have created a type y[-1] which is compatible with x, here -1 means the
  dimension is not specified, so it can be any size

  */

  return std::make_unique<BoundIndexExpression>(
      inner_type, std::move(bound_index_expressions),
      expression->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing