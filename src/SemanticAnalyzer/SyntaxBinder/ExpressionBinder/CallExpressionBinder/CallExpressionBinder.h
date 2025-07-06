#pragma once

#include "../../../../syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "../../../../utils/BuiltInFunction/BuiltInFunction.h"
#include "../../../BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"
#include <memory>
class CallExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};