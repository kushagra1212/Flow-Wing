#include "AttributeExpressionSyntax.h"

/*
    OVERIDES
*/

const SyntaxKindUtils::SyntaxKind AttributeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::BracketedExpression;
}

const std::vector<SyntaxNode *> &AttributeExpressionSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(_key.get());
    _children.push_back(_value.get());
  }

  return _children;
}

const DiagnosticUtils::SourceLocation
AttributeExpressionSyntax::getSourceLocation() const {
  return this->_key->getSourceLocation();
}