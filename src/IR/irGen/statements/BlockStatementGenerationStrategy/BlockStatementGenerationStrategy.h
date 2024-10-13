#ifndef __FLOWWING_BLOCK_STATEMENT_STRATEGY_H__
#define __FLOWWING_BLOCK_STATEMENT_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class BlockStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  BlockStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif // __FLOWWING_BLOCK_STATEMENT_STRATEGY_H__
