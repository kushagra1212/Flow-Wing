#pragma once

#include "../../../../../syntax/expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "../../../../BoundExpressions/BoundTypeExpression/BoundTypeExpression.h"
#include "../../ExpressionBinder.h"
#include "../TypeExpressionBinder.h"

class PrimitiveTypeExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};