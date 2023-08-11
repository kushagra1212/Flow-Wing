

#include "ParameterSyntax.h"

ParameterSyntax::ParameterSyntax(SyntaxToken<std::any> *identifierToken) {
  _identifierToken = identifierToken;
}

SyntaxToken<std::any> *ParameterSyntax::getIdentifierToken() const {
  return _identifierToken;
}

SyntaxKindUtils::SyntaxKind ParameterSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ParameterSyntax;
}

std::string ParameterSyntax::getLineNumberAndColumn() const {
  return _identifierToken->getLineNumberAndColumn();
}

std::vector<SyntaxNode *> ParameterSyntax::getChildren() {
  std::vector<SyntaxNode *> children = {};
  children.push_back(_identifierToken);
  return children;
}

ParameterSyntax::~ParameterSyntax() {
  if (_identifierToken != nullptr) {
    delete _identifierToken;
    _identifierToken = nullptr;
  }
}
