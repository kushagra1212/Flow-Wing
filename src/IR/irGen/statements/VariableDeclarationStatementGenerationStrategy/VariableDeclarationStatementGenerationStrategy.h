#ifndef __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__
#define __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class VariableDeclarationStatementGenerationStrategy
    : public StatementGenerationStrategy {
public:
  VariableDeclarationStatementGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif // __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__
