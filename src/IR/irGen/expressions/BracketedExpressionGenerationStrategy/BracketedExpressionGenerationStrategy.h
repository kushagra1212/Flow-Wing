#ifndef __FLOWWING__BRACKETED_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__BRACKETED_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../bind/BoundBracketedExpression/BoundBracketedExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class BracketedExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  BracketedExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  // Specialized for BoundBracketedExpression

  template <typename... Args>
  llvm::Value *wrappedExpression(BoundBracketedExpression *bracketedExpression,
                                 Args...);
};

#endif // __FLOWWING__BRACKETED_EXPRESSION_GENERATION_STRATEGY_H__
