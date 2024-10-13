#include "TernaryExpressionBinder.h"
#include <memory>

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