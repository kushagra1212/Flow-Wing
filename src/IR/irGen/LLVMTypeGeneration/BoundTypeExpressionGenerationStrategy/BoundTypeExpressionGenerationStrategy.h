#pragma once

#include "../LLVMTypeGenerationStrategy.h"

class BoundTypeExpressionGenerationStrategy
    : public LLVMTypeGenerationStrategy {
 public:
  BoundTypeExpressionGenerationStrategy(CodeGenerationContext *context)
      : LLVMTypeGenerationStrategy(context) {}

  llvm::Type *getType(BoundTypeExpression *expression) override;
};
