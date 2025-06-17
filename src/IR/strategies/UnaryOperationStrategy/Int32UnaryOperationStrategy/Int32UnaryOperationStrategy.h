#pragma once
#include "../UnaryOperationStrategy.h"

class Int32UnaryOperationStrategy : public UnaryOperationStrategy {
public:
  Int32UnaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *performOperation(llvm::Value *val,
                                BoundUnaryExpression *unaryExpression) override;

  llvm::Value *performOperation(
      llvm::Value *val,
      BinderKindUtils::BoundUnaryOperatorKind unaryOperator) override;
};