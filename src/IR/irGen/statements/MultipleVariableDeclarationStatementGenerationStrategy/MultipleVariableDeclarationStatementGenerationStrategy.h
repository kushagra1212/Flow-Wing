#ifndef __FLOWWING_IRGEN_STATEMENTS_MULTIPLE_VARIABLE_DECLARATION_STATEMENT_GENERATION_STRATEGY_H__
#define __FLOWWING_IRGEN_STATEMENTS_MULTIPLE_VARIABLE_DECLARATION_STATEMENT_GENERATION_STRATEGY_H__

#include "../../../../bind/BoundMultipleVariableDeclaration/BoundMultipleVariableDeclaration.h"
#include "../VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"

class MultipleVariableDeclarationStatementGenerationStrategy
    : public StatementGenerationStrategy {
public:
  MultipleVariableDeclarationStatementGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *declareGlobal(BoundStatement *statement);
  llvm::Value *declareLocal(BoundStatement *statement);
};

#endif