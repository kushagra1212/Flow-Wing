#pragma once

#include "../../../../syntax/expression/MultipleAssignmentExpressionSyntax/MultipleAssignmentExpressionSyntax.h"
#include "../../../BoundExpressions/BoundMultipleAssignmentExpression/BoundMultipleAssignmentExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"

class MultipleAssignmentExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};