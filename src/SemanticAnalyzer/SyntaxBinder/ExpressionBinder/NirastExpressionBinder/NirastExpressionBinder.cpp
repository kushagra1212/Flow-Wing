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

#include "NirastExpressionBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundNirastExpression/BoundNirastExpression.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/syntax/expression/NirastExpressionSyntax/NirastExpressionSyntax.h"
#include <memory>

std::unique_ptr<BoundExpression>
NirastExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                       ExpressionSyntax *expression) {

  NirastExpressionSyntax *nirastExpressionSyntax =
      static_cast<NirastExpressionSyntax *>(expression);

  std::unique_ptr<BoundNirastExpression> boundNirastExpression =
      std::make_unique<BoundNirastExpression>(
          nirastExpressionSyntax->getSourceLocation());

  std::unique_ptr<BoundLiteralExpression<std::any>> nirLitExpr(
      static_cast<BoundLiteralExpression<std::any> *>(
          ExpressionBinderFactory::create(
              nirastExpressionSyntax->getNirastExpressionRef()->getKind())
              ->bindExpression(
                  ctx, nirastExpressionSyntax->getNirastExpressionRef().get())
              .release()));

  boundNirastExpression->setNirastExpression(std::move(nirLitExpr));

  return std::move(boundNirastExpression);
}