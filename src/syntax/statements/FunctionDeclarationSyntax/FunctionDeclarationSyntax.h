#ifndef FUNCTIONDECLARATIONSYNTAX_H
#define FUNCTIONDECLARATIONSYNTAX_H

#include "../../../Common.h"
#include "../../MemberSyntax.h"

#include "../../SyntaxToken.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../ParameterSyntax/ParameterSyntax.h"
#include "../StatementSyntax.h"
class FunctionDeclarationSyntax : public MemberSyntax {

private:
  std::unique_ptr<SyntaxToken<std::any>> _functionKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _identifierToken;
  std::unique_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::vector<std::unique_ptr<ParameterSyntax>> _parameters;
  std::unique_ptr<SyntaxToken<std::any>> _closeParenthesisToken;
  std::unique_ptr<BlockStatementSyntax> _body;

public:
  FunctionDeclarationSyntax(
      std::unique_ptr<SyntaxToken<std::any>> functionKeyword,
      std::unique_ptr<SyntaxToken<std::any>> identifierToken,
      std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken,
      std::vector<std::unique_ptr<ParameterSyntax>> parameters,
      std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken,
      std::unique_ptr<BlockStatementSyntax> body);

  std::unique_ptr<SyntaxToken<std::any>> getFunctionKeyword();
  std::unique_ptr<SyntaxToken<std::any>> getIdentifierToken();
  std::unique_ptr<SyntaxToken<std::any>> getOpenParenthesisToken();
  std::vector<std::unique_ptr<ParameterSyntax>> getParameters();
  std::unique_ptr<SyntaxToken<std::any>> getCloseParenthesisToken();
  std::unique_ptr<BlockStatementSyntax> getBody();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};

#endif // FUNCTIONDECLARATIONSYNTAX_H