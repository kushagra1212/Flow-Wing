#ifndef __STRING_BINARY_OPERATION_STRATEGY_H__
#define __STRING_BINARY_OPERATION_STRATEGY_H__
#include "../BinaryOperationStrategy.h"

class StringBinaryOperationStrategy : public BinaryOperationStrategy {
public:
  StringBinaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) override;

  llvm::Value *createStringComparison(llvm::Value *lhsValue,
                                      llvm::Value *rhsValue,
                                      const std::string functionName,
                                      std::string operand = "==");

  llvm::Value *concatenateStrings(llvm::Value *lhs, llvm::Value *rhs);
};

#endif // __STRING_BINARY_OPERATION_STRATEGY_H__