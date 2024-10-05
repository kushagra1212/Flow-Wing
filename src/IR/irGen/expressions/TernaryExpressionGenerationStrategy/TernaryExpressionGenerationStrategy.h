#pragma once

#include "../../../../bind/BoundTernaryExpression//BoundTernaryExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class TernaryExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  TernaryExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;
};
