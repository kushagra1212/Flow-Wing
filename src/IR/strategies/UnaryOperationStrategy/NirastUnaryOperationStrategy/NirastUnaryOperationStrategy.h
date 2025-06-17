#pragma once
#include "../UnaryOperationStrategy.h"

class NirastUnaryOperationStrategy : public UnaryOperationStrategy {
public:
  NirastUnaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *performOperation(llvm::Value *val,
                                BoundUnaryExpression *unaryExpression) override;

  llvm::Value *performOperation(
      llvm::Value *val,
      BinderKindUtils::BoundUnaryOperatorKind unaryOperator) override;
};