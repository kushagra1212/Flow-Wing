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