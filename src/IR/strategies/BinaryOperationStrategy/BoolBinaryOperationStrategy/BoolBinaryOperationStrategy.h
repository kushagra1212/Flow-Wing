#ifndef __BOOL_BINARY_OPERATION_STRATEGY_H__
#define __BOOL_BINARY_OPERATION_STRATEGY_H__

#include "../BinaryOperationStrategy.h"
#include "../Int32BinaryOperationStrategy/Int32BinaryOperationStrategy.h"

class BoolBinaryOperationStrategy : public BinaryOperationStrategy {
public:
  BoolBinaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) override;

  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BinderKindUtils::BoundBinaryOperatorKind binaryOp) override;
};

#endif // __INT_BINARY_OPERATION_STRATEGY_H__