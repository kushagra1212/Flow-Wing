#include "VariableDeclarationSyntax.h"

SyntaxKindUtils::SyntaxKind VariableDeclarationSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::VariableDeclaration;
}

std::vector<SyntaxNode *> VariableDeclarationSyntax::getChildren() {
  if (_children.size())
    return this->_children;

  if (_keyword)
    _children.push_back(_keyword.get());

  if (_identifier)
    _children.push_back(_identifier.get());

  if (_typeExpr)
    _children.push_back(_typeExpr.get());

  if (_initializer) {
    _children.push_back(_initializer.get());
  }

  return this->_children;
}

DiagnosticUtils::SourceLocation
VariableDeclarationSyntax::getSourceLocation() const {
  return this->_keyword->getSourceLocation();
}
