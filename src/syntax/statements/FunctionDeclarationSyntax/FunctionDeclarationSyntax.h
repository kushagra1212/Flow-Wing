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
  std::shared_ptr<SyntaxToken<std::any>> _functionKeyword;
  std::shared_ptr<SyntaxToken<std::any>> _identifierToken;
  std::shared_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::vector<std::shared_ptr<ParameterSyntax>> _parameters;
  std::shared_ptr<SyntaxToken<std::any>> _closeParenthesisToken;
  std::shared_ptr<BlockStatementSyntax> _body;

public:
  FunctionDeclarationSyntax(
      std::shared_ptr<SyntaxToken<std::any>> functionKeyword,
      std::shared_ptr<SyntaxToken<std::any>> identifierToken,
      std::shared_ptr<SyntaxToken<std::any>> openParenthesisToken,
      std::vector<std::shared_ptr<ParameterSyntax>> parameters,
      std::shared_ptr<SyntaxToken<std::any>> closeParenthesisToken,
      std::shared_ptr<BlockStatementSyntax> body);

  std::shared_ptr<SyntaxToken<std::any>> getFunctionKeyword() const;
  std::shared_ptr<SyntaxToken<std::any>> getIdentifierToken() const;
  std::shared_ptr<SyntaxToken<std::any>> getOpenParenthesisToken() const;
  std::vector<std::shared_ptr<ParameterSyntax>> getParameters() const;
  std::shared_ptr<SyntaxToken<std::any>> getCloseParenthesisToken() const;
  std::shared_ptr<BlockStatementSyntax> getBody() const;

  SyntaxKindUtils::SyntaxKind getKind() override;

  std::vector<std::shared_ptr<SyntaxNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // FUNCTIONDECLARATIONSYNTAX_H