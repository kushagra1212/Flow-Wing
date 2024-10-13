#pragma once

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTernaryExpression//BoundTernaryExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class TernaryExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  TernaryExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;
};
