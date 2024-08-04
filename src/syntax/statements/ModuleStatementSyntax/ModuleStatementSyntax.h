#ifndef MODULE_STATEMENT_SYNTAX_H
#define MODULE_STATEMENT_SYNTAX_H

#include "../../SyntaxToken.h"
#include "../../expression/LiteralExpressionSyntax.h"
#include "../CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "../FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../StatementSyntax.h"
#include "../VariableDeclarationSyntax/VariableDeclarationSyntax.h"

class ModuleStatementSyntax : public StatementSyntax {
  std::unique_ptr<SyntaxToken<std::any>> _moduleKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _openBracketToken;
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _moduleName;
  std::unique_ptr<SyntaxToken<std::any>> _closeBracketToken;

  std::vector<std::unique_ptr<VariableDeclarationSyntax>> _variableStatements;
  std::vector<std::unique_ptr<FunctionDeclarationSyntax>> _functionStatements;
  std::vector<std::unique_ptr<CustomTypeStatementSyntax>> _customTypeStatements;

public:
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  inline auto
  addModuleKeyword(std::unique_ptr<SyntaxToken<std::any>> moduleKeyword)
      -> void {
    this->_moduleKeyword = std::move(moduleKeyword);
  }

  inline auto
  addOpenBracketToken(std::unique_ptr<SyntaxToken<std::any>> openBracketToken)
      -> void {
    this->_openBracketToken = std::move(openBracketToken);
  }

  inline auto
  addModuleName(std::unique_ptr<LiteralExpressionSyntax<std::any>> moduleName)
      -> void {
    this->_moduleName = std::move(moduleName);
  }

  inline auto
  addCloseBracketToken(std::unique_ptr<SyntaxToken<std::any>> closeBracketToken)
      -> void {
    this->_closeBracketToken = std::move(closeBracketToken);
  }

  inline auto
  addVariableStatement(std::unique_ptr<VariableDeclarationSyntax> member)
      -> void {
    _variableStatements.push_back(std::move(member));
  }

  inline auto addCustomTypeStatement(
      std::unique_ptr<CustomTypeStatementSyntax> customTypeStatement) -> void {
    _customTypeStatements.push_back(std::move(customTypeStatement));
  }

  inline auto
  addFunctionStatement(std::unique_ptr<FunctionDeclarationSyntax> function)
      -> void {
    _functionStatements.push_back(std::move(function));
  }

  std::unique_ptr<SyntaxToken<std::any>> &getModuleKeywordRef() {
    return _moduleKeyword;
  }

  std::unique_ptr<SyntaxToken<std::any>> &getOpenBracketTokenRef() {
    return _openBracketToken;
  }

  std::unique_ptr<LiteralExpressionSyntax<std::any>> &getModuleNameRef() {
    return _moduleName;
  }

  std::unique_ptr<SyntaxToken<std::any>> &getCloseBracketTokenRef() {
    return _closeBracketToken;
  }

  inline auto getVariableStatementsRef()
      -> const std::vector<std::unique_ptr<VariableDeclarationSyntax>> & {
    return _variableStatements;
  }

  inline auto getFunctionStatementsRef()
      -> const std::vector<std::unique_ptr<FunctionDeclarationSyntax>> & {
    return _functionStatements;
  }

  inline auto getCustomTypeStatementsRef()
      -> const std::vector<std::unique_ptr<CustomTypeStatementSyntax>> & {
    return _customTypeStatements;
  }
};

#endif