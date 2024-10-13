#include "FillExpressionBinder.h"
#include <memory>

std::unique_ptr<BoundExpression>
FillExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                     ExpressionSyntax *expression) {

  FillExpressionSyntax *fillExpression =
      static_cast<FillExpressionSyntax *>(expression);

  std::unique_ptr<BoundFillExpression> boundFillExpression =
      std::make_unique<BoundFillExpression>(
          fillExpression->getSourceLocation());

  if (fillExpression->getSizeToFillExpressionRef().get()) {
    boundFillExpression->setSizeToFill(std::move(
        ExpressionBinderFactory::create(
            fillExpression->getSizeToFillExpressionRef()->getKind())
            ->bindExpression(
                ctx, fillExpression->getSizeToFillExpressionRef().get())));
  }

  boundFillExpression->setElementToFill(
      std::move(ExpressionBinderFactory::create(
                    fillExpression->getElementExpressionRef()->getKind())
                    ->bindExpression(
                        ctx, fillExpression->getElementExpressionRef().get())));

  return std::move(boundFillExpression);
}