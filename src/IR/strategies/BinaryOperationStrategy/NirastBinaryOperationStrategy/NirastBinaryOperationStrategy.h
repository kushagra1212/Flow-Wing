#ifndef __NIRAST_BINARY_OPERATION_STRATEGY_H__
#define __NIRAST_BINARY_OPERATION_STRATEGY_H__

#include "../BinaryOperationStrategy.h"

class NirastBinaryOperationStrategy : public BinaryOperationStrategy {
public:
  NirastBinaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) override;
};

#endif