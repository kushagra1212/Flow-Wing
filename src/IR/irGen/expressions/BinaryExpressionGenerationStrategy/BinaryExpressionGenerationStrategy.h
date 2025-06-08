#ifndef __FLOWWING__BINARY_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__BINARY_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../context/utils/DynamicValueHandler/DynamicValueHandler.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
class BinaryExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  BinaryExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  void declare(BoundExpression *expression);

  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BinderKindUtils::BoundBinaryOperatorKind binaryOp);

  llvm::Value *getExpressionValue(BoundExpression *expression,
                                  bool &isClassType, int8_t &isDynamicValue);
};

#endif // __FLOWWING__BINARY_EXPRESSION_GENERATION_STRATEGY_H__
