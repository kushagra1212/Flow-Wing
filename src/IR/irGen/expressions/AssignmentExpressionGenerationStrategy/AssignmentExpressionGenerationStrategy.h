#ifndef __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../../../bind/BoundIndexExpression/BoundIndexExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

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
};

#endif // __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
