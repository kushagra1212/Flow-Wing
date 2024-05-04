#include "VariableDeclarationSyntax.h"

const SyntaxKindUtils::SyntaxKind VariableDeclarationSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::VariableDeclaration;
}

const std::vector<SyntaxNode *> &VariableDeclarationSyntax::getChildren() {
  if (_children.size())
    return this->_children;

  if (_exposeKeyword)
    _children.push_back(_exposeKeyword.get());

  if (_keyword)
    _children.push_back(_keyword.get());

  if (_identifier)
    _children.push_back(_identifier.get());

  if (_typeExpr)
    _children.push_back(_typeExpr.get());

  if (_newKeyword)
    _children.push_back(_newKeyword.get());

  if (_initializer) {
    _children.push_back(_initializer.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
VariableDeclarationSyntax::getSourceLocation() const {
  if (_exposeKeyword)
    return this->_exposeKeyword->getSourceLocation();
  if (_keyword)
    return this->_keyword->getSourceLocation();
  if (_identifier)
    return this->_identifier->getSourceLocation();
  if (_typeExpr)
    return this->_typeExpr->getSourceLocation();
  if (_initializer)
    return this->_initializer->getSourceLocation();
  return DiagnosticUtils::SourceLocation();
}
