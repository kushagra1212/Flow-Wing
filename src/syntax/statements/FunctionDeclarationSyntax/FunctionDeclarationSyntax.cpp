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

std::string FunctionDeclarationSyntax::getLineNumberAndColumn() const {
  return _functionKeyword->getLineNumberAndColumn();
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
  if (_functionKeyword != nullptr) {
    delete _functionKeyword;
    _functionKeyword = nullptr;
  }

  if (_identifierToken != nullptr) {
    delete _identifierToken;
    _identifierToken = nullptr;
  }

  if (_openParenthesisToken != nullptr) {
    delete _openParenthesisToken;
    _openParenthesisToken = nullptr;
  }

  for (ParameterSyntax *parameter : _parameters) {
    if (parameter != nullptr) {
      delete parameter;
      parameter = nullptr;
    }
  }
  _parameters.clear();

  if (_closeParenthesisToken != nullptr) {
    delete _closeParenthesisToken;
    _closeParenthesisToken = nullptr;
  }

  if (_body != nullptr) {
    delete _body;
    _body = nullptr;
  }
}
