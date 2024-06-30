#ifndef __FLOAT_BINARY_OPERATION_STRATEGY_H__
#define __FLOAT_BINARY_OPERATION_STRATEGY_H__

#include "../BinaryOperationStrategy.h"

class FloatBinaryOperationStrategy : public BinaryOperationStrategy {
public:
  FloatBinaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) override;
};

#endif // __FLOAT_BINARY_OPERATION_STRATEGY_H__