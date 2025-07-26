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

#include "TernaryExpressionBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTernaryExpression/BoundTernaryExpression.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/syntax/expression/TernaryExpressionSyntax/TernaryExpressionSyntax.h"

std::unique_ptr<BoundExpression>
TernaryExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                        ExpressionSyntax *expression) {
  TernaryExpressionSyntax *ternaryExpressionSyntax =
      static_cast<TernaryExpressionSyntax *>(expression);

  return std::make_unique<BoundTernaryExpression>(
      ternaryExpressionSyntax->getSourceLocation(),
      std::move(
          ExpressionBinderFactory::create(
              ternaryExpressionSyntax->getConditionExpressionRef()->getKind())
              ->bindExpression(
                  ctx,
                  ternaryExpressionSyntax->getConditionExpressionRef().get())),
      std::move(
          ExpressionBinderFactory::create(
              ternaryExpressionSyntax->getTrueExpressionRef()->getKind())
              ->bindExpression(
                  ctx, ternaryExpressionSyntax->getTrueExpressionRef().get())),
      std::move(
          ExpressionBinderFactory::create(
              ternaryExpressionSyntax->getFalseExpressionRef()->getKind())
              ->bindExpression(
                  ctx,
                  ternaryExpressionSyntax->getFalseExpressionRef().get())));
}