#include "ObjectExpressionSyntax.h"

const SyntaxKindUtils::SyntaxKind ObjectExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ObjectExpression;
}
const std::vector<SyntaxNode *> &ObjectExpressionSyntax::getChildren() {
  if (_children.empty()) {

    _children.push_back(_openBraceToken.get());
    _children.push_back(_closeBraceToken.get());

    for (auto &attribute : _attributes) {
      _children.push_back(attribute.get());
    }
  }

  return _children;
}
const DiagnosticUtils::SourceLocation
ObjectExpressionSyntax::getSourceLocation() const {
  if (_openBraceToken)
    return _openBraceToken->getSourceLocation();
  if (_closeBraceToken)
    return _closeBraceToken->getSourceLocation();

  if (_attributes.size() > 0)
    return _attributes[0]->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}