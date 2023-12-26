#ifndef __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../../../bind/BoundBracketedExpression/BoundBracketedExpression.h"
#include "../../../../bind/BoundIndexExpression/BoundIndexExpression.h"
#include "../BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "../ContainerAssignmentExpressionGenerationStrategy/ContainerAssignmentExpressionGenerationStrategy.h"
#include "../ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"

class AssignmentExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  AssignmentExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  // Specialized for BoundAssignmentExpression
  llvm::Value *handleLiteralExpressionAssignment(
      BoundAssignmentExpression *assignmentExpression);

  llvm::Value *handleIndexExpressionAssignment(
      BoundAssignmentExpression *assignmentExpression);

  // Global Specialized for BoundAssignmentExpression
  llvm::Value *handleGlobalLiteralExpressionAssignment(
      BoundAssignmentExpression *assignmentExpression);

  llvm::Value *handleGlobalIndexExpressionAssignment(
      llvm::GlobalVariable *variable, llvm::Value *indexValue, llvm::Value *rhs,
      const std::string &variableName);

  bool canGenerateLiteralExpressionAssignment(
      BoundAssignmentExpression *assignmentExpression);

  // Primitve Local Variable Assignment

  llvm::Value *
  handleTypedPrmitiveLocalVariableAssignment(const std::string &variableName,
                                             const Utils::type &variableType,
                                             llvm::Value *rhsValue);

  llvm::Value *
  handleUnTypedPrmitiveLocalVariableAssignment(const std::string &variableName,
                                               llvm::Value *rhsValue);

  llvm::Value *
  handlePrimitiveLocalVariableAssignment(const std::string &variableName,
                                         const Utils::type &variableType,
                                         llvm::Value *rhsValue);

  // Primitive Global Variable Assignment

  llvm::Value *handleTypedPrmitiveGlobalVariableAssignment(
      llvm::GlobalVariable *variable, const std::string &variableName,
      const Utils::type &variableType, llvm::Value *rhsValue);

  llvm::Value *
  handleUnTypedPrmitiveGlobalVariableAssignment(llvm::GlobalVariable *variable,
                                                const std::string &variableName,
                                                llvm::Value *rhsValue);

  llvm::Value *handlePrimitiveGlobalVariableAssignment(
      llvm::GlobalVariable *variable, const std::string &variableName,
      const Utils::type &variableType, llvm::Value *rhsValue);

private:
  std::string _variableName;
  llvm::AllocaInst *_allocaInst;
  llvm::GlobalVariable *_previousGlobalVariable;
  Utils::type _variableType;
  bool _isGlobal;
};

#endif // __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
