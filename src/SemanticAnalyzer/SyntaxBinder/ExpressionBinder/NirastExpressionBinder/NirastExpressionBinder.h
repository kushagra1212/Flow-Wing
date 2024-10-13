#pragma once

#include "../../../../syntax/expression/NirastExpressionSyntax/NirastExpressionSyntax.h"
#include "../../../BoundExpressions/BoundNirastExpression/BoundNirastExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"

class NirastExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};