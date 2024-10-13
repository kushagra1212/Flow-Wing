#pragma once

#include "../../../../syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "../../../../syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "../../../../syntax/expression/VariableExpressionSyntax/VariableExpressionSyntax.h"
#include "../../../BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "../../../BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../../BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "../ExpressionBinder.h"
#include "../ExpressionBinderFactory.h"

class IndexExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};