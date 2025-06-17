#pragma once
#include "../UnaryOperationStrategy.h"

class DoubleUnaryOperationStrategy : public UnaryOperationStrategy {
public:
  DoubleUnaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *performOperation(llvm::Value *val,
                                BoundUnaryExpression *unaryExpression) override;

  llvm::Value *performOperation(
      llvm::Value *val,
      BinderKindUtils::BoundUnaryOperatorKind unaryOperator) override;
};