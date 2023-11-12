#ifndef __FLOWWING_EXPRESSION_STATEMENT_STRATEGY_H__
#define __FLOWWING_EXPRESSION_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundExpressionStatement/BoundExpressionStatement.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ExpressionStatementGenerationStrategy
    : public StatementGenerationStrategy {
public:
  ExpressionStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif //__FLOWWING_EXPRESSION_STATEMENT_STRATEGY_H__
