#ifndef __FLOWWING_PARENTHESIZED_EXPRESSION_STRATEGY_H__
#define __FLOWWING_PARENTHESIZED_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundParenthesizedExpression/BoundParenthesizedExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class ParenthesizedExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  ParenthesizedExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;
};

#endif // __FLOWWING_PARENTHESIZED_EXPRESSION_STRATEGY_H__
