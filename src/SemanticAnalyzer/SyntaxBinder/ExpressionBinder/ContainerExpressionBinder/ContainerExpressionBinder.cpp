#include "ContainerExpressionBinder.h"
#include <memory>

std::unique_ptr<BoundExpression>
ContainerExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                          ExpressionSyntax *expression) {

  ContainerExpressionSyntax *containerExpression =
      static_cast<ContainerExpressionSyntax *>(expression);

  std::unique_ptr<BoundContainerExpression> boundContainerExpression =
      std::make_unique<BoundContainerExpression>(
          containerExpression->getSourceLocation());

  for (int i = 0; i < containerExpression->getElementsRef().size(); i++) {
    std::unique_ptr<BoundExpression> boundExpression =
        std::move(ExpressionBinderFactory::create(
                      containerExpression->getElementsRef()[i]->getKind())
                      ->bindExpression(
                          ctx, containerExpression->getElementsRef()[i].get()));

    boundContainerExpression->setElement(std::move(boundExpression));
  }

  return std::move(boundContainerExpression);
}