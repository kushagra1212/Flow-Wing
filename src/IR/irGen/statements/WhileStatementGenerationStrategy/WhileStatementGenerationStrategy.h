#ifndef __FLOWWING_WHILE_STATEMENT_STRATEGY_H__
#define __FLOWWING_WHILE_STATEMENT_STRATEGY_H__

#include "../../../../IR/context/utils/DynamicValueHandler/DynamicValueHandler.h"
#include "../../../../SemanticAnalyzer/BoundStatements/BoundWhileStatement/BoundWhileStatement.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class WhileStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  WhileStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif // __FLOWWING_WHILE_STATEMENT_STRATEGY_H__
