#pragma once

#include "../../../../syntax/expression/BinaryExpressionSyntax.h"
#include "../../../BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../ExpressionBinder.h"

class BinaryExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};