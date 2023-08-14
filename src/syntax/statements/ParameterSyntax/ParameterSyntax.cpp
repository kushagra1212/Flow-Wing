

#include "ParameterSyntax.h"

ParameterSyntax::ParameterSyntax(
    std::shared_ptr<SyntaxToken<std::any>> identifierToken) {
  _identifierToken = identifierToken;
}

std::shared_ptr<SyntaxToken<std::any>>
ParameterSyntax::getIdentifierToken() const {
  return _identifierToken;
}

SyntaxKindUtils::SyntaxKind ParameterSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ParameterSyntax;
}

std::string ParameterSyntax::getLineNumberAndColumn() const {
  return _identifierToken->getLineNumberAndColumn();
}

std::vector<std::shared_ptr<SyntaxNode>> ParameterSyntax::getChildren() {
  std::vector<std::shared_ptr<SyntaxNode>> children = {};
  children.push_back(_identifierToken);
  return children;
}
