#ifndef __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__
#define __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundVariableExpression/BoundVariableExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class VariableExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  VariableExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *handleGlobalVariable(const std::string &variableName,
                                    llvm::GlobalVariable *variable);
};

#endif // __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__
