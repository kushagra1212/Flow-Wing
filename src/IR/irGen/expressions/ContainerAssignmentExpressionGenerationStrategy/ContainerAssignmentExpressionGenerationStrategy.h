#ifndef __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundVariableExpression/BoundVariableExpression.h"
#include "../ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"

class ContainerAssignmentExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  ContainerAssignmentExpressionGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  const bool
  canGenerateExpressionAssignment(BoundVariableExpression *variableExpression);

  void setVariable(llvm::Value *var);
  void setContainerName(const std::string &containerName);

  llvm::Value *createExpression(llvm::ArrayType *arrayType,
                                llvm::Value *variable, llvm::Value *size,
                                llvm::Value *rhsSize, llvm::Value *rhsVariable,
                                llvm::ArrayType *rhsArrayType);

private:
  // LHS
  std::string _containerName;
  llvm::Value *_variable;
  llvm::ArrayType *_arrayType;
  llvm::Value *_size;

  // RHS
  llvm::Value *_rhsVariable;
  llvm::ArrayType *_rhsArrayType;
  llvm::Value *_rhsSize;
};

#endif // __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__
