#ifndef __INT_BINARY_OPERATION_STRATEGY_H__
#define __INT_BINARY_OPERATION_STRATEGY_H__

#include "../BinaryOperationStrategy.h"

class Int32BinaryOperationStrategy : public BinaryOperationStrategy {
public:
  Int32BinaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) override;

  llvm::Value *performOperation(
      llvm::Value *lhsValue, llvm::Value *rhsValue,
      BinderKindUtils::BoundBinaryOperatorKind binaryOperator) override;
};

#endif // __INT_BINARY_OPERATION_STRATEGY_H__