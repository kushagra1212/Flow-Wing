#include "FunctionDeclarationSyntax.h"

FunctionDeclarationSyntax::FunctionDeclarationSyntax(
    std::unique_ptr<SyntaxToken<std::any>> functionKeyword,
    std::unique_ptr<SyntaxToken<std::any>> identifierToken,
    std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken,
    std::vector<std::unique_ptr<ParameterSyntax>> parameters,
    std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken,
    std::unique_ptr<BlockStatementSyntax> body) {
  this->_functionKeyword = std::move(functionKeyword);
  this->_identifierToken = std::move(identifierToken);
  this->_openParenthesisToken = std::move(openParenthesisToken);
  this->_parameters = std::move(parameters);
  this->_closeParenthesisToken = std::move(closeParenthesisToken);
  this->_body = std::move(body);

  // Add children

  _children.push_back(_functionKeyword.get());
  _children.push_back(_identifierToken.get());
  _children.push_back(_openParenthesisToken.get());
  for (const std::unique_ptr<ParameterSyntax> &parameter : _parameters) {
    _children.push_back(parameter.get());
  }
  _children.push_back(_closeParenthesisToken.get());
  _children.push_back(_body.get());
}

std::unique_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getFunctionKeyword() {
  return std::move(_functionKeyword);
}

std::unique_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getIdentifierToken() {
  return std::move(_identifierToken);
}

std::unique_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getOpenParenthesisToken() {
  return std::move(_openParenthesisToken);
}

std::vector<std::unique_ptr<ParameterSyntax>>
FunctionDeclarationSyntax::getParameters() {
  return std::move(_parameters);
}

std::unique_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getCloseParenthesisToken() {
  return std::move(_closeParenthesisToken);
}

std::unique_ptr<BlockStatementSyntax> FunctionDeclarationSyntax::getBody() {
  return std::move(_body);
}

SyntaxKindUtils::SyntaxKind FunctionDeclarationSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax;
}

std::string FunctionDeclarationSyntax::getLineNumberAndColumn() {
  return _functionKeyword->getLineNumberAndColumn();
}

std::vector<SyntaxNode *> FunctionDeclarationSyntax::getChildren() {
  return this->_children;
}

std::unique_ptr<SyntaxToken<std::any>> &
FunctionDeclarationSyntax::getFunctionKeywordPtr() {
  return _functionKeyword;
}
std::unique_ptr<SyntaxToken<std::any>> &
FunctionDeclarationSyntax::getIdentifierTokenPtr() {
  return _identifierToken;
}
std::unique_ptr<SyntaxToken<std::any>> &
FunctionDeclarationSyntax::getOpenParenthesisTokenPtr() {
  return _openParenthesisToken;
}
std::vector<std::unique_ptr<ParameterSyntax>> &
FunctionDeclarationSyntax::getParametersPtr() {
  return _parameters;
}
std::unique_ptr<SyntaxToken<std::any>> &
FunctionDeclarationSyntax::getCloseParenthesisTokenPtr() {
  return _closeParenthesisToken;
}
std::unique_ptr<BlockStatementSyntax> &FunctionDeclarationSyntax::getBodyPtr() {
  return _body;
}
