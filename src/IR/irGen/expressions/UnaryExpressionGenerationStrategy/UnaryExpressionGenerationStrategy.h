#ifndef __FLOWWING__UNARY_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__UNARY_EXPRESSION_GENERATION_STRATEGY_H__

#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class UnaryExpressionGenerationStrategy : public ExpressionGenerationStrategy {
 public:
  UnaryExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;
};

#endif  // __FLOWWING__UNARY_EXPRESSION_GENERATION_STRATEGY_H__
