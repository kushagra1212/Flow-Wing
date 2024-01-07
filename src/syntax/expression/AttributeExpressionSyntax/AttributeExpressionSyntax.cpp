#include "AttributeExpressionSyntax.h"

/*
    OVERIDES
*/

SyntaxKindUtils::SyntaxKind AttributeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::BracketedExpression;
}

std::vector<SyntaxNode *> AttributeExpressionSyntax::getChildren() {

  if (_children.empty()) {
    _children.push_back(_key.get());
    _children.push_back(_value.get());
  }

  return _children;
}

DiagnosticUtils::SourceLocation
AttributeExpressionSyntax::getSourceLocation() const {
  return this->_key->getSourceLocation();
}