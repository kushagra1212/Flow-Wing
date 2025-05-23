#ifndef __FLOWWING_MODULE_STATEMENT_GENERATION_STRATEGY_H__
#define __FLOWWING_MODULE_STATEMENT_GENERATION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundStatements/BoundModuleStatement/BoundModuleStatement.h"
#include "../../expressions/CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "../ClassStatementGenerationStrategy/ClassStatementGenerationStrategy.h"
#include "../CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../FunctionDeclarationGenerationStrategy/FunctionDeclarationGenerationStrategy.h"
#include "../VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"

class ModuleStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  ModuleStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;

  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *declare(BoundStatement *statement);
};

#endif // __FLOWWING_MODULE_STATEMENT_GENERATION_STRATEGY_H__
