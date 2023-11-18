#ifndef __FLOWWING_CALL_EXPRESSION_STRATEGY_H__
#define __FLOWWING_CALL_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundCallExpression/BoundCallExpression.h"
#include "../../../../bind/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class CallExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  CallExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *buildInFunctionCall(BoundCallExpression *callExpression);
  llvm::Value *userDefinedFunctionCall(BoundCallExpression *callExpression);

  llvm::Value *printArray(llvm::AllocaInst *v);
  llvm::Value *printGlobalArray(llvm::GlobalVariable *v);
};

#endif // __FLOWWING_CALL_EXPRESSION_STRATEGY_H__
