#ifndef __FLOWWING_LITERAL_EXPRESSION_STRATEGY_H__
#define __FLOWWING_LITERAL_EXPRESSION_STRATEGY_H__

#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class LiteralExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  LiteralExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;
};

#endif // __FLOWWING_LITERAL_EXPRESSION_STRATEGY_H__
