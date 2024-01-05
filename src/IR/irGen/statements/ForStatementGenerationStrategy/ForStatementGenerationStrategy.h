#ifndef __FLOWWING_FOR_STATEMENT_STRATEGY_H__
#define __FLOWWING_FOR_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundForStatement/BoundForStatement.h"
#include "../../expressions/AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
#include "../../expressions/VariableExpressionGenerationStrategy/VariableExpressionGenerationStrategy.h"
#include "../../statements/VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"
class ForStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  ForStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::PHINode *generateLoopCondition(llvm::Value *stepValue,
                                       llvm::Value *value,
                                       llvm::Value *upperBound);
};

#endif // __FLOWWING_FOR_STATEMENT_STRATEGY_H__
