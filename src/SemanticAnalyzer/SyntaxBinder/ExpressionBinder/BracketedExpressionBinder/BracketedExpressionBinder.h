#pragma once

#include "../../../../syntax/expression/BracketedExpressionSyntax/BracketedExpressionSyntax.h"
#include "../../../BoundExpressions/BoundBracketedExpression/BoundBracketedExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"

class BracketedExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};