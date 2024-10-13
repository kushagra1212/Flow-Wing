#pragma once

#include "../../../../syntax/expression/ContainerExpressionSyntax/ContainerExpressionSyntax.h"
#include "../../../BoundExpressions/BoundContainerExpression/BoundContainerExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"

class ContainerExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};