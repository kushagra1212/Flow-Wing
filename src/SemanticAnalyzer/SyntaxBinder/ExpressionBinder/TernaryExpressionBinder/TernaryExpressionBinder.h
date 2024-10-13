#pragma once

#include "../../../../syntax/expression/TernaryExpressionSyntax/TernaryExpressionSyntax.h"
#include "../../../BoundExpressions/BoundTernaryExpression/BoundTernaryExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"

class TernaryExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};