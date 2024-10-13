#include "NirastExpressionBinder.h"
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