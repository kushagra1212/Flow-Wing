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

#include "FillExpressionBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundFillExpression/BoundFillExpression.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/syntax/expression/FillExpressionSyntax/FillExpressionSyntax.h"

std::unique_ptr<BoundExpression>
FillExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                     ExpressionSyntax *expression) {

  FillExpressionSyntax *fillExpression =
      static_cast<FillExpressionSyntax *>(expression);

  std::unique_ptr<BoundFillExpression> boundFillExpression =
      std::make_unique<BoundFillExpression>(
          fillExpression->getSourceLocation());

  if (fillExpression->getSizeToFillExpressionRef().get()) {
    boundFillExpression->setSizeToFill(std::move(
        ExpressionBinderFactory::create(
            fillExpression->getSizeToFillExpressionRef()->getKind())
            ->bindExpression(
                ctx, fillExpression->getSizeToFillExpressionRef().get())));
  }

  boundFillExpression->setElementToFill(
      std::move(ExpressionBinderFactory::create(
                    fillExpression->getElementExpressionRef()->getKind())
                    ->bindExpression(
                        ctx, fillExpression->getElementExpressionRef().get())));

  return std::move(boundFillExpression);
}