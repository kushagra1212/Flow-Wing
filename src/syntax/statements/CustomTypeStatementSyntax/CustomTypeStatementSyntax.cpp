#include "CustomTypeStatementSyntax.h"

/*
    OVERRIDES

*/

SyntaxKindUtils::SyntaxKind CustomTypeStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::CustomTypeStatement;
}

std::vector<SyntaxNode *> CustomTypeStatementSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  _children.push_back(this->_typeName.get());

  for (const auto &keyTypePair : this->_key_type_pairs) {
    _children.push_back(keyTypePair.get());
  }

  return _children;
}

DiagnosticUtils::SourceLocation
CustomTypeStatementSyntax::getSourceLocation() const {

  return this->_typeName->getSourceLocation();
}