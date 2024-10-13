#include "ParenthesizedExpressionBinder.h"
#include <memory>

#include "../ExpressionBinderFactory.h"

std::unique_ptr<BoundExpression>
ParenthesizedExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                              ExpressionSyntax *expression) {
  ParenthesizedExpressionSyntax *parenthesizedExpression =
      (ParenthesizedExpressionSyntax *)expression;

  return std::move(
      ExpressionBinderFactory::create(
          parenthesizedExpression->getExpressionRef()->getKind())
          ->bindExpression(ctx,
                           parenthesizedExpression->getExpressionRef().get()));
}