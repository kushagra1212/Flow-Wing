#pragma once

#include "../../../../../syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include "../../../../BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../ExpressionBinder.h"
#include "../TypeExpressionBinder.h"

class ObjectTypeExpressionBinder : public ExpressionBinder {
public:
  std::unique_ptr<BoundExpression> bindExpression(SyntaxBinderContext *ctx,
                                                  ExpressionSyntax *expression);
};