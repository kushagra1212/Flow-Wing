#pragma once

#include "../../../../syntax/expression/LiteralExpressionSyntax.h"
#include "../../../BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../ExpressionBinder.h"

class LiteralExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};