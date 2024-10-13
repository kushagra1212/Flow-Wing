#pragma once

#include "../../../syntax/expression/ExpressionSyntax.h"
#include "../../BoundExpressions/BoundExpression/BoundExpression.h"
#include "../SyntaxBinderContext/SyntaxBinderContext.h"

class ExpressionBinder {
public:
  virtual ~ExpressionBinder() = default;
  virtual std::unique_ptr<BoundExpression>
  bindExpression(SyntaxBinderContext *ctx, ExpressionSyntax *expression) = 0;
};