#ifndef FUNCTIONDECLARATIONSYNTAX_H
#define FUNCTIONDECLARATIONSYNTAX_H

#include "../../../Common.h"
#include "../../MemberSyntax.h"

#include "../../../utils/Utils.h"
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
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> _separators;
  std::unique_ptr<SyntaxToken<std::any>> _closeParenthesisToken;
  std::unique_ptr<BlockStatementSyntax> _body;
  Utils::type _returnType;

public:
  FunctionDeclarationSyntax();

  std::unique_ptr<SyntaxToken<std::any>> getFunctionKeyword();
  std::unique_ptr<SyntaxToken<std::any>> getIdentifierToken();
  std::unique_ptr<SyntaxToken<std::any>> getOpenParenthesisToken();
  std::unique_ptr<SyntaxToken<std::any>> getCloseParenthesisToken();
  std::unique_ptr<BlockStatementSyntax> getBody();
  Utils::type getReturnType();

  void
  setFunctionKeyword(std::unique_ptr<SyntaxToken<std::any>> functionKeyword);
  void
  setIdentifierToken(std::unique_ptr<SyntaxToken<std::any>> identifierToken);
  void setOpenParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken);
  void addParameter(std::unique_ptr<ParameterSyntax> parameter);
  void addSeparator(std::unique_ptr<SyntaxToken<std::any>> separator);
  void setCloseParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken);
  void setBody(std::unique_ptr<BlockStatementSyntax> body);
  void setReturnType(Utils::type returnType);

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getFunctionKeywordPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getIdentifierTokenPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getOpenParenthesisTokenPtr();
  std::vector<std::unique_ptr<ParameterSyntax>> &getParametersPtr();
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> &getSeparatorsPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getCloseParenthesisTokenPtr();
  std::unique_ptr<BlockStatementSyntax> &getBodyPtr();
};

#endif // FUNCTIONDECLARATIONSYNTAX_H