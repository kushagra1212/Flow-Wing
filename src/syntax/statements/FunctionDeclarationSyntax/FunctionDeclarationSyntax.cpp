#include "FunctionDeclarationSyntax.h"

FunctionDeclarationSyntax::FunctionDeclarationSyntax(
    std::shared_ptr<SyntaxToken<std::any>> functionKeyword,
    std::shared_ptr<SyntaxToken<std::any>> identifierToken,
    std::shared_ptr<SyntaxToken<std::any>> openParenthesisToken,
    std::vector<std::shared_ptr<ParameterSyntax>> parameters,
    std::shared_ptr<SyntaxToken<std::any>> closeParenthesisToken,
    std::shared_ptr<BlockStatementSyntax> body) {
  _functionKeyword = functionKeyword;
  _identifierToken = identifierToken;
  _openParenthesisToken = openParenthesisToken;
  _parameters = parameters;
  _closeParenthesisToken = closeParenthesisToken;
  _body = body;
}

std::shared_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getFunctionKeyword() const {
  return _functionKeyword;
}

std::shared_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getIdentifierToken() const {
  return _identifierToken;
}

std::shared_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getOpenParenthesisToken() const {
  return _openParenthesisToken;
}

std::vector<std::shared_ptr<ParameterSyntax>>
FunctionDeclarationSyntax::getParameters() const {
  return _parameters;
}

std::shared_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getCloseParenthesisToken() const {
  return _closeParenthesisToken;
}

std::shared_ptr<BlockStatementSyntax>
FunctionDeclarationSyntax::getBody() const {
  return _body;
}

SyntaxKindUtils::SyntaxKind FunctionDeclarationSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax;
}

std::string FunctionDeclarationSyntax::getLineNumberAndColumn() const {
  return _functionKeyword->getLineNumberAndColumn();
}

std::vector<std::shared_ptr<SyntaxNode>>
FunctionDeclarationSyntax::getChildren() {
  std::vector<std::shared_ptr<SyntaxNode>> children = {};
  children.push_back(_functionKeyword);
  children.push_back(_identifierToken);
  children.push_back(_openParenthesisToken);
  for (std::shared_ptr<ParameterSyntax> parameter : _parameters) {
    children.push_back(parameter);
  }
  children.push_back(_closeParenthesisToken);
  children.push_back((_body));
  return children;
}
