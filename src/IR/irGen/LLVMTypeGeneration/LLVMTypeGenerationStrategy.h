#pragma once

#include "../GenerationStrategy.h"

class LLVMTypeGenerationStrategy : public GenerationStrategy {
 public:
  LLVMTypeGenerationStrategy(CodeGenerationContext *context)
      : GenerationStrategy(context) {}

  virtual llvm::Type *getType(BoundTypeExpression *expression) = 0;

  virtual ~LLVMTypeGenerationStrategy() = default;
};
