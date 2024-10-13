#include "ObjectExpressionBinder.h"
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