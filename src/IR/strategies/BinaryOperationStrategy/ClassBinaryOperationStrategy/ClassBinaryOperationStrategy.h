#pragma once
#include "../BinaryOperationStrategy.h"

class ClassBinaryOperationStrategy : public BinaryOperationStrategy {
public:
  ClassBinaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) override;

  llvm::Value *performOperation(
      llvm::Value *lhsValue, llvm::Value *rhsValue,
      BinderKindUtils::BoundBinaryOperatorKind binaryOperator) override;
};