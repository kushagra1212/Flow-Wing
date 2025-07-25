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


#include "UnaryExpressionBinder.h"

#include "../ExpressionBinderFactory.h"

std::unique_ptr<BoundExpression>
UnaryExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                      ExpressionSyntax *expression) {
  UnaryExpressionSyntax *unaryExpression =
      static_cast<UnaryExpressionSyntax *>(expression);

  std::unique_ptr<BoundExpression> boundOperand = std::move(
      ExpressionBinderFactory::create(
          unaryExpression->getOperandRef()->getKind())
          ->bindExpression(ctx, unaryExpression->getOperandRef().get()));

  BinderKindUtils::BoundUnaryOperatorKind op =
      BinderKindUtils::getUnaryOperatorKind(
          unaryExpression->getOperatorTokenRef()->getKind());

  return std::make_unique<BoundUnaryExpression>(
      unaryExpression->getSourceLocation(), op, std::move(boundOperand));
}