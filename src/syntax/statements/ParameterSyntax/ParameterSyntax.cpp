

#include "ParameterSyntax.h"

ParameterSyntax::ParameterSyntax(
    std::unique_ptr<SyntaxToken<std::any>> identifierToken) {
  this->_identifierToken = std::move(identifierToken);

  // Add children

  _children.push_back(_identifierToken.get());
}

SyntaxKindUtils::SyntaxKind ParameterSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ParameterSyntax;
}

DiagnosticUtils::SourceLocation ParameterSyntax::getSourceLocation() const {
  return this->_identifierToken->getSourceLocation();
}

std::vector<SyntaxNode *> ParameterSyntax::getChildren() {
  return this->_children;
}

std::unique_ptr<SyntaxToken<std::any>> &
ParameterSyntax::getIdentifierTokenPtr() {
  return this->_identifierToken;
}