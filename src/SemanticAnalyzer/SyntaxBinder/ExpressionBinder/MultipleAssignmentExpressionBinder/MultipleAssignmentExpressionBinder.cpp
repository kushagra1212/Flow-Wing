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

#include "MultipleAssignmentExpressionBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundMultipleAssignmentExpression/BoundMultipleAssignmentExpression.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/syntax/expression/MultipleAssignmentExpressionSyntax/MultipleAssignmentExpressionSyntax.h"

std::unique_ptr<BoundExpression>
MultipleAssignmentExpressionBinder::bindExpression(
    SyntaxBinderContext *ctx, ExpressionSyntax *expression) {
  MultipleAssignmentExpressionSyntax *multipleAssignmentExpressionSyntax =
      static_cast<MultipleAssignmentExpressionSyntax *>(expression);

  std::unique_ptr<BoundMultipleAssignmentExpression>
      boundMultipleAssignmentExpression =
          std::make_unique<BoundMultipleAssignmentExpression>(
              multipleAssignmentExpressionSyntax->getSourceLocation());

  for (const auto &assignment :
       multipleAssignmentExpressionSyntax->getAssignmentExprListRef()) {
    boundMultipleAssignmentExpression->addAssignment(
        std::unique_ptr<BoundAssignmentExpression>(
            (BoundAssignmentExpression *)ExpressionBinderFactory::create(
                assignment->getKind())
                ->bindExpression(ctx, assignment.get())
                .release()));
  }

  return std::move(boundMultipleAssignmentExpression);
}