#include "ContainerStatementSyntax.h"
ContainerStatementSyntax::ContainerStatementSyntax(
    Utils::type type,
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression) {
  this->_type = type;
  this->_identifierExpression = std::move(identifierExpression);
}

std::vector<SyntaxNode *> ContainerStatementSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  _children.push_back(this->_identifierExpression.get());
  for (auto &item : this->_items)
    _children.push_back(item.get());

  return _children;
}
SyntaxKindUtils::SyntaxKind ContainerStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ContainerStatement;
}
DiagnosticUtils::SourceLocation
ContainerStatementSyntax::getSourceLocation() const {
  return this->_identifierExpression->getSourceLocation();
}

void ContainerStatementSyntax::addItem(std::unique_ptr<ExpressionSyntax> item) {
  this->_items.push_back(std::move(item));
}

std::unique_ptr<LiteralExpressionSyntax<std::any>> &
ContainerStatementSyntax::getIdentifierExpression() {
  return this->_identifierExpression;
}
std::vector<std::unique_ptr<ExpressionSyntax>> &
ContainerStatementSyntax::getItems() {
  return this->_items;
}
Utils::type ContainerStatementSyntax::getType() const { return this->_type; }