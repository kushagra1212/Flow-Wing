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

  const bool canGenerateExpressionAssignment(BoundExpression *expr);

  void setVariable(llvm::Value *var);
  void setContainerName(const std::string &containerName);

  llvm::Value *createExpression(llvm::ArrayType *&arrayType,
                                llvm::Value *&variable,
                                llvm::Value *&rhsVariable,
                                llvm::ArrayType *&rhsArrayType,
                                llvm::Type *arrayElementType,
                                const std::vector<size_t> &lhsSizes,
                                const std::vector<size_t> &rhsSizes);

  void assignArray(llvm::ArrayType *&arrayType, llvm::Value *&variable,
                   llvm::Value *&rhsVariable, llvm::ArrayType *&rhsArrayType,
                   llvm::Type *rhsArrayElementType,
                   std::vector<llvm::Value *> &indices,
                   const std::vector<size_t> &rhsSizes, uint64_t index);

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

  std::vector<size_t> _lhsSizes, _rhsSizes;
  llvm::Type *_rhsArrayElementType, *_lhsArrayElementType;
};

#endif  // __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__
