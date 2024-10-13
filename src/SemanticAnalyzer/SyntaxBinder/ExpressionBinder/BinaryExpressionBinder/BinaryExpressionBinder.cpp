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