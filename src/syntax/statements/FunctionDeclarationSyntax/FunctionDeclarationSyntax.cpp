#include "FunctionDeclarationSyntax.h"

FunctionDeclarationSyntax::FunctionDeclarationSyntax(
    SyntaxToken<std::any> *functionKeyword,
    SyntaxToken<std::any> *identifierToken,
    SyntaxToken<std::any> *openParenthesisToken,
    std::vector<ParameterSyntax *> parameters,
    SyntaxToken<std::any> *closeParenthesisToken, BlockStatementSyntax *body) {
  _functionKeyword = functionKeyword;
  _identifierToken = identifierToken;
  _openParenthesisToken = openParenthesisToken;
  _parameters = parameters;
  _closeParenthesisToken = closeParenthesisToken;
  _body = body;
}

SyntaxToken<std::any> *FunctionDeclarationSyntax::getFunctionKeyword() const {
  return _functionKeyword;
}

SyntaxToken<std::any> *FunctionDeclarationSyntax::getIdentifierToken() const {
  return _identifierToken;
}

SyntaxToken<std::any> *
FunctionDeclarationSyntax::getOpenParenthesisToken() const {
  return _openParenthesisToken;
}

std::vector<ParameterSyntax *>
FunctionDeclarationSyntax::getParameters() const {
  return _parameters;
}

SyntaxToken<std::any> *
FunctionDeclarationSyntax::getCloseParenthesisToken() const {
  return _closeParenthesisToken;
}

BlockStatementSyntax *FunctionDeclarationSyntax::getBody() const {
  return _body;
}

SyntaxKindUtils::SyntaxKind FunctionDeclarationSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax;
}

std::vector<SyntaxNode *> FunctionDeclarationSyntax::getChildren() {
  std::vector<SyntaxNode *> children = {};
  children.push_back(_functionKeyword);
  children.push_back(_identifierToken);
  children.push_back(_openParenthesisToken);
  for (ParameterSyntax *parameter : _parameters) {
    children.push_back(parameter);
  }
  children.push_back(_closeParenthesisToken);
  children.push_back((_body));
  return children;
}

FunctionDeclarationSyntax::~FunctionDeclarationSyntax() {
  delete _functionKeyword;
  delete _identifierToken;
  delete _openParenthesisToken;
  for (ParameterSyntax *parameter : _parameters) {
    delete parameter;
  }
  delete _closeParenthesisToken;
  delete _body;
}