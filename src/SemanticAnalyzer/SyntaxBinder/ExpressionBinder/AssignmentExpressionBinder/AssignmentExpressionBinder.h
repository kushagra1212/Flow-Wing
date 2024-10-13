#pragma once

#include "../../../../syntax/expression/AssignmentExpressionSyntax.h"
#include "../../../../syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "../../../../syntax/expression/VariableExpressionSyntax/VariableExpressionSyntax.h"
#include "../../../BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../ExpressionBinder.h"
class AssignmentExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};