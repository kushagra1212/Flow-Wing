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

  llvm::Value *getVariableValue(const std::string &variableName);

  llvm::Value *getGlobalVariableValue(const std::string &variableName,
                                      llvm::GlobalVariable *variable);

  // Get Primitive Local Variable Value

  llvm::Value *getTypedPrimitiveLocalVariableValue(
      const std::string &variableName, llvm::Value *variableValue,
      llvm::AllocaInst *v);

  llvm::Value *getUnTypedLocalVariableValue(llvm::Value *variableValue,
                                            llvm::AllocaInst *v,
                                            const std::string &variableName);

  llvm::Value *getLocalVariableValue(const std::string &variableName,
                                     llvm::Value *variableValue,
                                     llvm::AllocaInst *v);
};

#endif  // __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__
