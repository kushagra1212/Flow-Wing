#pragma once

#include "../LLVMTypeGenerationStrategy.h"

class BoundArrayTypeExpressionGenerationStrategy
    : public LLVMTypeGenerationStrategy {
 public:
  BoundArrayTypeExpressionGenerationStrategy(CodeGenerationContext *context)
      : LLVMTypeGenerationStrategy(context) {}

  llvm::Type *getType(BoundTypeExpression *expression) override;
};
