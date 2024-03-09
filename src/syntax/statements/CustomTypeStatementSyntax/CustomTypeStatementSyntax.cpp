#include "CustomTypeStatementSyntax.h"

/*
    OVERRIDES

*/

const SyntaxKindUtils::SyntaxKind CustomTypeStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::CustomTypeStatement;
}

const std::vector<SyntaxNode *> &CustomTypeStatementSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  if (this->_exposeKeyword)
    _children.push_back(this->_exposeKeyword.get());

  _children.push_back(this->_typeName.get());

  for (const auto &keyTypePair : this->_key_type_pairs) {
    _children.push_back(keyTypePair.get());
  }

  return _children;
}

const DiagnosticUtils::SourceLocation
CustomTypeStatementSyntax::getSourceLocation() const {
  return this->_typeName->getSourceLocation();
}