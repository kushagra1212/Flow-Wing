#ifndef __FLOWWING_IRGEN_STATEMENTS_MULTIPLE_VARIABLE_DECLARATION_STATEMENT_GENERATION_STRATEGY_H__
#define __FLOWWING_IRGEN_STATEMENTS_MULTIPLE_VARIABLE_DECLARATION_STATEMENT_GENERATION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "../../../../SemanticAnalyzer/BoundStatements/BoundMultipleVariableDeclaration/BoundMultipleVariableDeclaration.h"
#include "../../../../SemanticAnalyzer/BoundUtils.h"
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

  void handleMultipleVarDecReturnCallExprDeclare(
      BoundMultipleVariableDeclaration *multipleVariableDeclaration);
  void handleMultipleVarDecCallExprGen(
      BoundMultipleVariableDeclaration *multipleVariableDeclaration);

  bool hasSingleCallExpr(
      BoundMultipleVariableDeclaration *multipleVariableDeclaration);
};

#endif