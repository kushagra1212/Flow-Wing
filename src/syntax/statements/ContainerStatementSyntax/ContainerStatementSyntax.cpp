#include "ContainerStatementSyntax.h"

/*
  OVERRIDES
*/

std::vector<SyntaxNode *> ContainerStatementSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  _children.push_back(this->_identifierToken.get());
  for (auto &value : this->_values)
    _children.push_back(value.get());

  return _children;
}

SyntaxKindUtils::SyntaxKind ContainerStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ContainerStatement;
}

DiagnosticUtils::SourceLocation
ContainerStatementSyntax::getSourceLocation() const {
  return this->_identifierToken->getSourceLocation();
}

/*
  SETTERS
*/

auto ContainerStatementSyntax::setValue(std::unique_ptr<ExpressionSyntax> value)
    -> void {
  this->_values.push_back(std::move(value));
}

auto ContainerStatementSyntax::setContainerSizeExpression(
    std::unique_ptr<ExpressionSyntax> exp) -> void {
  this->_containerSizeExpression = std::move(exp);
}

auto ContainerStatementSyntax::setIdentifierToken(
    std::unique_ptr<SyntaxToken<std::any>> identifierToken) -> void {
  this->_identifierToken = std::move(identifierToken);
}

auto ContainerStatementSyntax::setType(Utils::type type) -> void {
  this->_type = type;
}

auto ContainerStatementSyntax::setKeyword(
    std::unique_ptr<SyntaxToken<std::any>> keyword) -> void {
  this->_keyword = std::move(keyword);
}

/*
  GETTERS
*/

const std::unique_ptr<SyntaxToken<std::any>> &
ContainerStatementSyntax::getIdentifierTokenRef() const {
  return this->_identifierToken;
}

const std::vector<std::unique_ptr<ExpressionSyntax>> &
ContainerStatementSyntax::getValuesRef() const {
  return this->_values;
}

const std::unique_ptr<ExpressionSyntax> &
ContainerStatementSyntax::getContainerSizeExpressionRef() const {
  return this->_containerSizeExpression;
}

const Utils::type &ContainerStatementSyntax::getType() const {
  return this->_type;
}
