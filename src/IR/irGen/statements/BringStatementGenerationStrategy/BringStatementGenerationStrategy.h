#ifndef __FLOWWING_BRING_STATEMENT_STRATEGY_H__
#define __FLOWWING_BRING_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundBringStatement/BoundBringStatement.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class BringStatementGenerationStrategy : public StatementGenerationStrategy {
 public:
  BringStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif  //__FLOWWING_BRING_STATEMENT_STRATEGY_H__
