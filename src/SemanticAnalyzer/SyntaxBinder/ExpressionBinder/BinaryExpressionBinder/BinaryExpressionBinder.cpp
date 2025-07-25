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


#include "BinaryExpressionBinder.h"

#include "../ExpressionBinderFactory.h"

std::unique_ptr<BoundExpression>
BinaryExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                       ExpressionSyntax *expression) {

  BinaryExpressionSyntax *binaryExpression =
      static_cast<BinaryExpressionSyntax *>(expression);

  std::unique_ptr<BoundExpression> boundLeft = std::move(
      ExpressionBinderFactory::create(binaryExpression->getLeftRef()->getKind())
          ->bindExpression(ctx, binaryExpression->getLeftRef().get()));

  std::unique_ptr<BoundExpression> boundRight = std::move(
      ExpressionBinderFactory::create(
          binaryExpression->getRightRef()->getKind())
          ->bindExpression(ctx, binaryExpression->getRightRef().get()));

  BinderKindUtils::BoundBinaryOperatorKind op =
      BinderKindUtils::getBinaryOperatorKind(
          binaryExpression->getOperatorTokenRef()->getKind());

  return std::make_unique<BoundBinaryExpression>(
      binaryExpression->getSourceLocation(), std::move(boundLeft), op,
      std::move(boundRight));
}