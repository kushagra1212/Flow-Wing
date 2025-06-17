#pragma once

#include "../UnaryOperationStrategy.h"

class BoolUnaryOperationStrategy : public UnaryOperationStrategy {
public:
  BoolUnaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *performOperation(llvm::Value *val,
                                BoundUnaryExpression *unaryExpression) override;

  llvm::Value *performOperation(
      llvm::Value *val,
      BinderKindUtils::BoundUnaryOperatorKind unaryOperator) override;
};
