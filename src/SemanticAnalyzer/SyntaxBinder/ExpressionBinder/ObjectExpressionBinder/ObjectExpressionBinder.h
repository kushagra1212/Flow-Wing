#pragma once

#include "../../../../syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "../../../BoundExpressions/BoundObjectExpression/BoundObjectExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"

class ObjectExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};