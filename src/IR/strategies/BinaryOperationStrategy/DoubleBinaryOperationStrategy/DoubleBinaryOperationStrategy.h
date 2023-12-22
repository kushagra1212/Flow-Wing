#ifndef __DOUBLE_BINARY_OPERATION_STRATEGY_H__
#define __DOUBLE_BINARY_OPERATION_STRATEGY_H__

#include "../BinaryOperationStrategy.h"

class DoubleBinaryOperationStrategy : public BinaryOperationStrategy {
public:
  DoubleBinaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) override;
};

#endif // __INT_BINARY_OPERATION_STRATEGY_H__