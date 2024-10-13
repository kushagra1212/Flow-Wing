#ifndef __FLOWWING_BREAK_STATEMENT_STRATEGY_H__
#define __FLOWWING_BREAK_STATEMENT_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundStatements/BoundBreakStatement/BoundBreakStatement.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class BreakStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  BreakStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif //__FLOWWING_BREAK_STATEMENT_STRATEGY_H__
