#ifndef MODULE_STATEMENT_SYNTAX_H
#define MODULE_STATEMENT_SYNTAX_H

#include "../../SyntaxToken.h"
#include "../../expression/LiteralExpressionSyntax.h"
#include "../ClassStatementSyntax/ClassStatementSyntax.h"
#include "../CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "../FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../StatementSyntax.h"
#include "../VariableDeclarationSyntax/VariableDeclarationSyntax.h"

class ModuleStatementSyntax : public StatementSyntax {
  std::unique_ptr<SyntaxToken<std::any>> _moduleKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _openBracketToken;
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _moduleName;
  std::unique_ptr<SyntaxToken<std::any>> _closeBracketToken;

  std::vector<std::unique_ptr<SyntaxNode>> _statements;

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

  inline auto addStatement(std::unique_ptr<SyntaxNode> statement) -> void {
    _statements.push_back(std::move(statement));
  }

  const inline std::unique_ptr<SyntaxToken<std::any>> &getModuleKeywordRef() {
    return _moduleKeyword;
  }

  inline std::unique_ptr<SyntaxToken<std::any>> &getOpenBracketTokenRef() {
    return _openBracketToken;
  }

  inline std::unique_ptr<LiteralExpressionSyntax<std::any>> &
  getModuleNameRef() {
    return _moduleName;
  }

  std::unique_ptr<SyntaxToken<std::any>> &getCloseBracketTokenRef() {
    return _closeBracketToken;
  }

  inline auto getStatementsRef()
      -> const std::vector<std::unique_ptr<SyntaxNode>> & {
    return _statements;
  }
};

#endif