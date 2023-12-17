#ifndef __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../../../bind/BoundBracketedExpression/BoundBracketedExpression.h"
#include "../../../../bind/BoundContainerExpression/BoundContainerExpression.h"
#include "../../../../bind/BoundFillExpression/BoundFillExpression.h"
#include "../../../../bind/BoundIndexExpression/BoundIndexExpression.h"
#include "../ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../FillExpressionGenerationStrategy/FillExpressionGenerationStrategy.h"

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

  // Specialized for BoundAssignmentExpression

  llvm::Value *handleBracketedAssignment(BoundExpression *expression);

private:
  std::string _variableName;
  llvm::Value *_previousValue;
  Utils::type _variableType;
  bool _isGlobal;
};

#endif // __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
