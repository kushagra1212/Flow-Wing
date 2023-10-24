#include "FunctionDeclarationSyntax.h"

FunctionDeclarationSyntax::FunctionDeclarationSyntax(const bool &isExposed)
    : MemberSyntax(isExposed) {

  // Add children
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

std::unique_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getCloseParenthesisToken() {
  return std::move(_closeParenthesisToken);
}

std::unique_ptr<BlockStatementSyntax> FunctionDeclarationSyntax::getBody() {
  return std::move(_body);
}

Utils::type FunctionDeclarationSyntax::getReturnType() { return _returnType; }

SyntaxKindUtils::SyntaxKind FunctionDeclarationSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax;
}

DiagnosticUtils::SourceLocation
FunctionDeclarationSyntax::getSourceLocation() const {
  return _functionKeyword->getSourceLocation();
}

std::vector<SyntaxNode *> FunctionDeclarationSyntax::getChildren() {

  if (this->_children.size() == 0) {

    _children.push_back(_functionKeyword.get());
    _children.push_back(_identifierToken.get());
    _children.push_back(_openParenthesisToken.get());

    for (int i = 0; i < _parameters.size(); i++) {
      _children.push_back(_parameters[i].get());
      if (i < _separators.size()) {
        _children.push_back(_separators[i].get());
      }
    }

    _children.push_back(_closeParenthesisToken.get());
    _children.push_back(_body.get());
  }
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

std::vector<std::unique_ptr<SyntaxToken<std::any>>> &
FunctionDeclarationSyntax::getSeparatorsPtr() {
  return _separators;
}

std::unique_ptr<SyntaxToken<std::any>> &
FunctionDeclarationSyntax::getCloseParenthesisTokenPtr() {
  return _closeParenthesisToken;
}
std::unique_ptr<BlockStatementSyntax> &FunctionDeclarationSyntax::getBodyPtr() {
  return _body;
}

void FunctionDeclarationSyntax::setFunctionKeyword(
    std::unique_ptr<SyntaxToken<std::any>> functionKeyword) {
  _functionKeyword = std::move(functionKeyword);
}

void FunctionDeclarationSyntax::setIdentifierToken(
    std::unique_ptr<SyntaxToken<std::any>> identifierToken) {
  _identifierToken = std::move(identifierToken);
}

void FunctionDeclarationSyntax::setOpenParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken) {
  _openParenthesisToken = std::move(openParenthesisToken);
}

void FunctionDeclarationSyntax::addParameter(
    std::unique_ptr<ParameterSyntax> parameter) {
  _parameters.push_back(std::move(parameter));
}

void FunctionDeclarationSyntax::setCloseParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken) {
  _closeParenthesisToken = std::move(closeParenthesisToken);
}

void FunctionDeclarationSyntax::setBody(
    std::unique_ptr<BlockStatementSyntax> body) {
  _body = std::move(body);
}

void FunctionDeclarationSyntax::setReturnType(Utils::type returnType) {
  _returnType = returnType;
}

void FunctionDeclarationSyntax::addSeparator(
    std::unique_ptr<SyntaxToken<std::any>> separator) {
  _separators.push_back(std::move(separator));
}
