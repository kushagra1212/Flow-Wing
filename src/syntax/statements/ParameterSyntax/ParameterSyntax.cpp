

#include "ParameterSyntax.h"

ParameterSyntax::ParameterSyntax(
    std::unique_ptr<SyntaxToken<std::any>> identifierToken) {
  this->_identifierToken = std::move(identifierToken);
}

const SyntaxKindUtils::SyntaxKind ParameterSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ParameterSyntax;
}

const DiagnosticUtils::SourceLocation ParameterSyntax::getSourceLocation()
    const {
  return this->_identifierToken->getSourceLocation();
}

const std::vector<SyntaxNode *> &ParameterSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_identifierToken.get());
  }

  return this->_children;
}

std::unique_ptr<SyntaxToken<std::any>> &
ParameterSyntax::getIdentifierTokenPtr() {
  return this->_identifierToken;
}