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
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundNewExpression/BoundNewExpression.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/syntax/expression/NewExpressionSyntax/NewExpressionSyntax.h"

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression>
ExpressionBinder::bindNewExpression(syntax::NewExpressionSyntax *node) {

  auto expression = bind(node->getExpression().get());

  if (expression->getKind() == NodeKind::kErrorExpression) {
    return expression;
  }

  return std::make_unique<BoundNewExpression>(std::move(expression),
                                              node->getSourceLocation());

} // namespace binding
} // namespace binding
} // namespace flow_wing