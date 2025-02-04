#ifndef __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

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
                                const std::vector<uint64_t> &lhsSizes,
                                const std::vector<uint64_t> &rhsSizes);

  void assignArray(llvm::ArrayType *&arrayType, llvm::Value *&variable,
                   llvm::Value *&rhsVariable, llvm::ArrayType *&rhsArrayType,
                   llvm::Type *rhsArrayElementType,
                   std::vector<llvm::Value *> &indices,
                   const std::vector<uint64_t> &rhsSizes, uint64_t index);

  llvm::Value *createExpressionForObject(BoundExpression *expression,
                                         llvm::ArrayType *&arrayType,
                                         llvm::Value *&variable,
                                         const std::vector<uint64_t> &sizes,
                                         llvm::Type *&elementType);

  llvm::Value *assignVariable(BoundAssignmentExpression *assignmentExpression);

private:
  // LHS
  std::string _containerName;
  llvm::Value *_variable = nullptr;
  llvm::ArrayType *_arrayType = nullptr;
  llvm::Value *_size = nullptr;

  // RHS
  llvm::Value *_rhsVariable = nullptr;
  llvm::ArrayType *_rhsArrayType = nullptr;
  llvm::Value *_rhsSize = nullptr;

  std::vector<uint64_t> _lhsSizes, _rhsSizes;
  llvm::Type *_rhsArrayElementType = nullptr, *_lhsArrayElementType = nullptr;
};

#endif // __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__
