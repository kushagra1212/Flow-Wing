#ifndef __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__
#define __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "../../../../SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "../../../context/utils/DynamicValueHandler/DynamicValueHandler.h"
#include "../../expressions/AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
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

  llvm::Value *handleTypedPrimitiveLocalVariableDeclaration(
      const std::string &variableName,
      const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value *rhsValue);

  llvm::Value *handleDynamicValuePrimitiveLocalVariableDeclare(
      const std::string &variableName, llvm::Value *rhsValue);

  llvm::Value *handlePrimitiveLocalVariableDeclaration(
      const std::string &variableName,
      const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value *rhsValue);

  llvm::Value *
  generateCommonStatement(BoundVariableDeclaration *variableDeclaration);

private:
  std::string _variableName;
  llvm::Value *_rhsValue = nullptr;
  int8_t m_isLHSDynamicValue = 0;
  SyntaxKindUtils::SyntaxKind _variableType;
  BoundVariableDeclaration *_variableDeclaration = nullptr;
  bool _isGlobal = false;

  llvm::Value *declare();
  void populateVariables(BoundStatement *statement,
                         BinderKindUtils::MemoryKind memoryKind =
                             BinderKindUtils::MemoryKind::None);
};

#endif // __FLOWWING_VARIABLE_DECLARATION_STATEMENT_STRATEGY_H__
