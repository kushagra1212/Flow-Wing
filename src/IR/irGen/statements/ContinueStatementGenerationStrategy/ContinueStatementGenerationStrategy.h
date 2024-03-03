#ifndef __FLOWWING_CONTINUE_STATEMENT_STRATEGY_H__
#define __FLOWWING_CONTINUE_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundContinueStatement/BoundContinueStatement.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ContinueStatementGenerationStrategy : public StatementGenerationStrategy {
 public:
  ContinueStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif  //__FLOWWING_CONTINUE_STATEMENT_STRATEGY_H__
