#include "IndexExpressionSyntax.h"

IndexExpressionSyntax::IndexExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression,
    std::unique_ptr<LiteralExpressionSyntax<std::any>> indexToken) {
  this->_identifierExpression = std::move(identifierExpression);
  this->_indexExpression = std::move(indexToken);
}

std::unique_ptr<LiteralExpressionSyntax<std::any>> &
IndexExpressionSyntax::getIndexIdentifierExpressionPtr() {
  return this->_identifierExpression;
}
std::unique_ptr<LiteralExpressionSyntax<std::any>> &
IndexExpressionSyntax::getIndexEpressionPtr() {
  return this->_indexExpression;
}

SyntaxKindUtils::SyntaxKind IndexExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::IndexExpression;
}
std::vector<SyntaxNode *> IndexExpressionSyntax::getChildren() {

  if (_children.size() > 0)
    return _children;

  _children.push_back(this->_identifierExpression.get());
  _children.push_back(this->_indexExpression.get());
  return _children;
}
DiagnosticUtils::SourceLocation
IndexExpressionSyntax::getSourceLocation() const {
  return this->_indexExpression->getSourceLocation();
}