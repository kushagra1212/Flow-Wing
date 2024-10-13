#pragma once
#include "../../../../SemanticAnalyzer/BoundStatements/BoundSwitchStatement/BoundSwitchStatement.h"
#include "../../expressions/BinaryExpressionGenerationStrategy/BinaryExpressionGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class SwitchStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  SwitchStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  void
  populateSwitchStatementsBasicBlock(std::vector<llvm::BasicBlock *> &casesBB,
                                     const uint64_t &casesSize,
                                     llvm::Function *&function);

  void populateSwitchExpressionValue(llvm::Value *&expressionValue,
                                     BoundExpression *expression);
};
