#ifndef __FLOWWING_MODULE_STATEMENT_GENERATION_STRATEGY_H__
#define __FLOWWING_MODULE_STATEMENT_GENERATION_STRATEGY_H__

#include "../../../../bind/BoundModuleStatement/BoundModuleStatement.h"
#include "../CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../FunctionDeclarationGenerationStrategy/FunctionDeclarationGenerationStrategy.h"

class ModuleStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  ModuleStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;

  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *declare(BoundStatement *statement);
};

#endif // __FLOWWING_MODULE_STATEMENT_GENERATION_STRATEGY_H__
