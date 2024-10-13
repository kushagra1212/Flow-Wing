#pragma once

#include "../../../../syntax/expression/FillExpressionSyntax/FillExpressionSyntax.h"
#include "../../../BoundExpressions/BoundFillExpression/BoundFillExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"

class FillExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};