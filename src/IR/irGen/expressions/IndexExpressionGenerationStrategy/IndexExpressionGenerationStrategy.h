#ifndef __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__
#define __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundIndexExpression/BoundIndexExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class IndexExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  IndexExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;
};

#endif // __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__
