#ifndef __FLOWWING_MULTIPLE_ASSIGNMENT_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING_MULTIPLE_ASSIGNMENT_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundMultipleAssignmentExpression/BoundMultipleAssignmentExpression.h"
#include "../../../../SemanticAnalyzer/BoundUtils.h"
#include "../AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
class MultipleAssignmentExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  MultipleAssignmentExpressionGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  void declare(BoundExpression *expression);

  void handleMultipleVarAssignCallExprGen(
      BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression);

  bool hasSingleCallExpr(
      BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression);
};

#endif