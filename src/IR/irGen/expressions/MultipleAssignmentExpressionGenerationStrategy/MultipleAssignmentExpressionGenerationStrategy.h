#ifndef __FLOWWING_MULTIPLE_ASSIGNMENT_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING_MULTIPLE_ASSIGNMENT_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../bind/BoundCallExpression/BoundCallExpression.h"
#include "../../../../bind/BoundMultipleAssignmentExpression/BoundMultipleAssignmentExpression.h"
#include "../../../../bind/BoundUtils.h"
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