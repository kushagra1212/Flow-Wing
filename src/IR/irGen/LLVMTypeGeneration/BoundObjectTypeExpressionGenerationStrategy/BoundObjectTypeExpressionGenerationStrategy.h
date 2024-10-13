#pragma once

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../LLVMTypeGenerationStrategy.h"

class BoundObjectTypeExpressionGenerationStrategy
    : public LLVMTypeGenerationStrategy {
public:
  BoundObjectTypeExpressionGenerationStrategy(CodeGenerationContext *context)
      : LLVMTypeGenerationStrategy(context) {}

  llvm::Type *getType(BoundTypeExpression *expression) override;
};
