#pragma once
#include "../UnaryOperationStrategy.h"

class StringUnaryOperationStrategy : public UnaryOperationStrategy {
public:
  StringUnaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *performOperation(llvm::Value *val,
                                BoundUnaryExpression *unaryExpression) override;

  llvm::Value *performOperation(
      llvm::Value *val,
      BinderKindUtils::BoundUnaryOperatorKind unaryOperator) override;
};