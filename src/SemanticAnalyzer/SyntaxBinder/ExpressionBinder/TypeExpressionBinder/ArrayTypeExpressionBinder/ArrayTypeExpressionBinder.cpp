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

#include "ArrayTypeExpressionBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundArrayTypeExpression/BoundArrayTypeExpression.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/syntax/expression/TypeExpressionSyntax/ArrayTypeExpressionSyntax/ArrayTypeExpressionSyntax.h"
#include <memory>

std::unique_ptr<BoundExpression>
ArrayTypeExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                          ExpressionSyntax *expression) {
  ArrayTypeExpressionSyntax *arrayTypeExpressionSyntax =
      static_cast<ArrayTypeExpressionSyntax *>(expression);

  std::unique_ptr<BoundArrayTypeExpression> boundArrayTypeExpression =
      std::make_unique<BoundArrayTypeExpression>(
          arrayTypeExpressionSyntax->getSourceLocation(),
          arrayTypeExpressionSyntax->getTypeRef()->getKind());

  if (arrayTypeExpressionSyntax->isTrivial()) {
    boundArrayTypeExpression->setElementType(
        arrayTypeExpressionSyntax->getElementTypeRef()->getKind());
  } else {
    std::unique_ptr<BoundTypeExpression> boundTypeExpr(static_cast<
                                                       BoundTypeExpression *>(
        ExpressionBinderFactory::create(
            arrayTypeExpressionSyntax->getNonTrivialElementTypeRef()->getKind())
            ->bindExpression(
                ctx,
                arrayTypeExpressionSyntax->getNonTrivialElementTypeRef().get())
            .release()));

    boundArrayTypeExpression->setNonTrivialElementType(
        std::move(boundTypeExpr));
  }

  for (const auto &size : arrayTypeExpressionSyntax->getDimensions()) {
    boundArrayTypeExpression->addDimension(
        std::move(ExpressionBinderFactory::create(size->getKind())
                      ->bindExpression(ctx, size.get())));
  }

  return std::move(boundArrayTypeExpression);
}