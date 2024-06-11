#ifndef __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__
#define __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundCallExpression/BoundCallExpression.h"
#include "../../../../bind/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "../../expressions/LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
#include "../../expressions/ObjectExpressionGenerationStrategy/ObjectExpressionGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class VariableDeclarationStatementGenerationStrategy
    : public StatementGenerationStrategy {
public:
  VariableDeclarationStatementGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

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
  bool _isGlobal = false;
};

#endif // __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__
