#ifndef __FLOWWING__CONTAINER_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__CONTAINER_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../bind/BoundContainerExpression/BoundContainerExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

template <typename AS, typename ET, typename CN>
class ContainerExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  ContainerExpressionGenerationStrategy(CodeGenerationContext *context);

  ContainerExpressionGenerationStrategy(CodeGenerationContext *context,
                                        AS actualSize, ET elementType,
                                        CN containerName);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

private:
  AS m_actualSize;
  ET m_elementType;
  CN m_containerName;
};

#endif // __FLOWWING__CONTAINER_EXPRESSION_GENERATION_STRATEGY_H__
