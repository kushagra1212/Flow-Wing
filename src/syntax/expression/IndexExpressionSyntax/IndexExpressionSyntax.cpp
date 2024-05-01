#include "IndexExpressionSyntax.h"

IndexExpressionSyntax::IndexExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression) {
  this->_identifierExpression = std::move(identifierExpression);
}

std::unique_ptr<LiteralExpressionSyntax<std::any>> &
IndexExpressionSyntax::getIndexIdentifierExpressionPtr() {
  return this->_identifierExpression;
}

const SyntaxKindUtils::SyntaxKind IndexExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::IndexExpression;
}
const std::vector<SyntaxNode *> &IndexExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  _children.push_back(this->_identifierExpression.get());

  for (const auto &item : this->_indexExpressions) {
    _children.push_back(item.get());
  }
  if (_variableExpression) {
    _children.push_back(_variableExpression.get());
  }
  return _children;
}
const DiagnosticUtils::SourceLocation
IndexExpressionSyntax::getSourceLocation() const {
  return this->_identifierExpression->getSourceLocation();
}