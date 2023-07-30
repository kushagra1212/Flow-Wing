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
  SyntaxToken<std::any> *_functionKeyword;
  SyntaxToken<std::any> *_identifierToken;
  SyntaxToken<std::any> *_openParenthesisToken;
  std::vector<ParameterSyntax *> _parameters;
  SyntaxToken<std::any> *_closeParenthesisToken;
  BlockStatementSyntax *_body;

public:
  FunctionDeclarationSyntax(SyntaxToken<std::any> *functionKeyword,
                            SyntaxToken<std::any> *identifierToken,
                            SyntaxToken<std::any> *openParenthesisToken,
                            std::vector<ParameterSyntax *> parameters,
                            SyntaxToken<std::any> *closeParenthesisToken,
                            BlockStatementSyntax *body);

  SyntaxToken<std::any> *getFunctionKeyword() const;
  SyntaxToken<std::any> *getIdentifierToken() const;
  SyntaxToken<std::any> *getOpenParenthesisToken() const;
  std::vector<ParameterSyntax *> getParameters() const;
  SyntaxToken<std::any> *getCloseParenthesisToken() const;
  BlockStatementSyntax *getBody() const;

  SyntaxKindUtils::SyntaxKind getKind() override;

  std::vector<SyntaxNode *> getChildren() override;
};

#endif // FUNCTIONDECLARATIONSYNTAX_H