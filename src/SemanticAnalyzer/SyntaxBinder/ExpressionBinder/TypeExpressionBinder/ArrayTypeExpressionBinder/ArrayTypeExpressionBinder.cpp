#include "ArrayTypeExpressionBinder.h"
#include <memory>

std::unique_ptr<BoundExpression>
ArrayTypeExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                          ExpressionSyntax *expression) {
  ArrayTypeExpressionSyntax *arrayTypeExpressionSyntax =
      static_cast<ArrayTypeExpressionSyntax *>(expression);

  std::unique_ptr<BoundArrayTypeExpression> boundArrayTypeExpression =
      std::make_unique<BoundArrayTypeExpression>(
          arrayTypeExpressionSyntax->getSourceLocation(),
          arrayTypeExpressionSyntax->getTypeRef()->getKind());

  if (arrayTypeExpressionSyntax->isTrivial()) {
    boundArrayTypeExpression->setElementType(
        arrayTypeExpressionSyntax->getElementTypeRef()->getKind());
  } else {
    std::unique_ptr<BoundTypeExpression> boundTypeExpr(static_cast<
                                                       BoundTypeExpression *>(
        ExpressionBinderFactory::create(
            arrayTypeExpressionSyntax->getNonTrivialElementTypeRef()->getKind())
            ->bindExpression(
                ctx,
                arrayTypeExpressionSyntax->getNonTrivialElementTypeRef().get())
            .release()));

    boundArrayTypeExpression->setNonTrivialElementType(
        std::move(boundTypeExpr));
  }

  for (const auto &size : arrayTypeExpressionSyntax->getDimensions()) {
    boundArrayTypeExpression->addDimension(
        std::move(ExpressionBinderFactory::create(size->getKind())
                      ->bindExpression(ctx, size.get())));
  }

  return std::move(boundArrayTypeExpression);
}