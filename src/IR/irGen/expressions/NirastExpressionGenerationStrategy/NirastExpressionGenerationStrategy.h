#ifndef __NIRAST_EXPRESSION_GENERATION_STRATEGY_H__
#define __NIRAST_EXPRESSION_GENERATION_STRATEGY_H__

#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class NirastExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  NirastExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *generate();
};

#endif