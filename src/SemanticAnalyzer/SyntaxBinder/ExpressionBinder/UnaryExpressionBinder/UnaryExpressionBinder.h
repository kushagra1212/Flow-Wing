#pragma once

#include "../../../../syntax/expression/UnaryExpressionSyntax.h"
#include "../../../BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../ExpressionBinder.h"

class UnaryExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};