#include "LiteralExpressionBinder.h"

std::unique_ptr<BoundExpression>
LiteralExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                        ExpressionSyntax *expression) {
  LiteralExpressionSyntax<std::any> *literalSyntax =
      static_cast<LiteralExpressionSyntax<std::any> *>(expression);

  std::any value = literalSyntax->getValue();

  return std::make_unique<BoundLiteralExpression<std::any>>(
      literalSyntax->getSourceLocation(), value,
      literalSyntax->getSyntaxKind());
}