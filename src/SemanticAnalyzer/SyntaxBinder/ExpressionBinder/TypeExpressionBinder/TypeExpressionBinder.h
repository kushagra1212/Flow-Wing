#pragma once

#include "../../../../syntax/expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "../../../BoundExpressions/BoundTypeExpression/BoundTypeExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"

class TypeExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};