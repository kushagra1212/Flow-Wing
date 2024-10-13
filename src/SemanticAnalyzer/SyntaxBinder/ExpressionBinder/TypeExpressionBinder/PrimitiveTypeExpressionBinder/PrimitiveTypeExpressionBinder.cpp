#include "PrimitiveTypeExpressionBinder.h"
#include <memory>

std::unique_ptr<BoundExpression>
PrimitiveTypeExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                              ExpressionSyntax *expression) {
  TypeExpressionSyntax *typeExpressionSyntax =
      static_cast<TypeExpressionSyntax *>(expression);

  return std::move(std::make_unique<BoundTypeExpression>(
      typeExpressionSyntax->getSourceLocation(),
      typeExpressionSyntax->getTypeRef()->getKind()));
}