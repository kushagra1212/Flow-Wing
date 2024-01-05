#include "IndexExpressionSyntax.h"

IndexExpressionSyntax::IndexExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression) {
  this->_identifierExpression = std::move(identifierExpression);
}

std::unique_ptr<LiteralExpressionSyntax<std::any>> &
IndexExpressionSyntax::getIndexIdentifierExpressionPtr() {
  return this->_identifierExpression;
}

SyntaxKindUtils::SyntaxKind IndexExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::IndexExpression;
}
std::vector<SyntaxNode *> IndexExpressionSyntax::getChildren() {

  if (_children.size() > 0)
    return _children;

  _children.push_back(this->_identifierExpression.get());

  for (const auto &item : this->_indexExpressions) {
    _children.push_back(item.get());
  }

  return _children;
}
DiagnosticUtils::SourceLocation
IndexExpressionSyntax::getSourceLocation() const {
  return this->_identifierExpression->getSourceLocation();
}