#ifndef __FLOWWING_BRING_STATEMENT_STRATEGY_H__
#define __FLOWWING_BRING_STATEMENT_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "../../../../SemanticAnalyzer/BoundStatements/BoundBringStatement/BoundBringStatement.h"
#include "../../../../utils/Utils.h"
#include "../../expressions/CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "../ClassStatementGenerationStrategy/ClassStatementGenerationStrategy.h"
#include "../CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../ModuleStatementGenerationStrategy/ModuleStatementGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"
#include "../VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"

class BringStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  BringStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
  llvm::Value *declare(BoundStatement *statement);
};

#endif //__FLOWWING_BRING_STATEMENT_STRATEGY_H__
