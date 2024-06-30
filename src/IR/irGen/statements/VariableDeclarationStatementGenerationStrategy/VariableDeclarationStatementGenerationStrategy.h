#ifndef __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__
#define __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundCallExpression/BoundCallExpression.h"
#include "../../../../bind/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../../expressions/LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
#include "../../expressions/ObjectExpressionGenerationStrategy/ObjectExpressionGenerationStrategy.h"
#include "../ContainerDeclarationStatementGenerationStrategy/ContainerDeclarationStatementGenerationStrategy.h"
#include "../ObjectDeclarationStatementGenerationStrategy/ObjectDeclarationStatementGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class VariableDeclarationStatementGenerationStrategy
    : public StatementGenerationStrategy {

public:
  VariableDeclarationStatementGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *declareGlobal(BoundStatement *statement);
  llvm::Value *declareLocal(BoundStatement *statement);

  // Specialized for BoundVariableDeclaration

  bool canGenerateStatement(BoundStatement *statement);

  // Local Primitive Variable Declaration

  llvm::Value *handleTypedPrimitiveLocalVariableDeclr(
      const std::string &variableName,
      const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value *rhsValue);

  llvm::Value *
  handleUnTypedPrimitiveLocalVariableDeclr(const std::string &variableName,
                                           llvm::Value *rhsValue);

  llvm::Value *handlePrimitiveLocalVariableDeclr(
      const std::string &variableName,
      const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value *rhsValue);

  llvm::Value *
  generateCommonStatement(BoundVariableDeclaration *variableDeclaration);

private:
  std::string _variableName;
  llvm::Value *_rhsValue;
  SyntaxKindUtils::SyntaxKind _variableType;
  BoundVariableDeclaration *_variableDeclaration;
  bool _isGlobal = false;

  llvm::Value *declare();
  void populateLocalVariables(BoundStatement *statement,
                              BinderKindUtils::MemoryKind memoryKind =
                                  BinderKindUtils::MemoryKind::None);
};

#endif // __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__
