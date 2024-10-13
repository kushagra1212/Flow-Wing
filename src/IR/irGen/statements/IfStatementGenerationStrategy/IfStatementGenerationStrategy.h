#ifndef __FLOWWING_IF_STATEMENT_STRATEGY_H__
#define __FLOWWING_IF_STATEMENT_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundStatements/BoundIfStatement/BoundIfStatement.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class IfStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  IfStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif // __FLOWWING_IF_STATEMENT_STRATEGY_H__
