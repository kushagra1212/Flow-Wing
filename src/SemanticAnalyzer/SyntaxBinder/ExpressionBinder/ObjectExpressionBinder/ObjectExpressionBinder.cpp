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

#include "ObjectExpressionBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include <memory>

std::unique_ptr<BoundExpression>
ObjectExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                       ExpressionSyntax *expression) {

  ObjectExpressionSyntax *objectExpressionSyntax =
      static_cast<ObjectExpressionSyntax *>(expression);

  std::unique_ptr<BoundObjectExpression> boundObjectExpression =
      std::make_unique<BoundObjectExpression>(
          objectExpressionSyntax->getSourceLocation());

  for (const auto &attribute : objectExpressionSyntax->getAttributes()) {

    std::unique_ptr<BoundLiteralExpression<std::any>> key(
        static_cast<BoundLiteralExpression<std::any> *>(
            ExpressionBinderFactory::create(attribute->getKey()->getKind())
                ->bindExpression(ctx, attribute->getKey().get())
                .release()));

    boundObjectExpression->addKeyValuePair(
        std::move(key),
        std::move(
            ExpressionBinderFactory::create(attribute->getValue()->getKind())
                ->bindExpression(ctx, attribute->getValue().get())));
  }

  return std::move(boundObjectExpression);
}