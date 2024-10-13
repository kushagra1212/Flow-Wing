#pragma once

#include "../../../../../syntax/expression/TypeExpressionSyntax/FunctionTypeExpressionSyntax/FunctionTypeExpressionSyntax.h"
#include "../../../../BoundExpressions/BoundTypeExpression/BoundFunctionTypeExpression/BoundFunctionTypeExpression.h"
#include "../../ExpressionBinder.h"
#include "../TypeExpressionBinder.h"

class FunctionTypeExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};