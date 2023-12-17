#include "ContainerStatementSyntax.h"

/*
  OVERRIDES
*/

std::vector<SyntaxNode *> ContainerStatementSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  _children.push_back(this->_identifierToken.get());
  _children.push_back(this->_containerExpression.get());

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

auto ContainerStatementSyntax::setContainerExpression(
    std::unique_ptr<ExpressionSyntax> containerExpression) -> void {
  this->_containerExpression = std::move(containerExpression);
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

const std::unique_ptr<ExpressionSyntax> &
ContainerStatementSyntax::getContainerSizeExpressionRef() const {
  return this->_containerSizeExpression;
}

const Utils::type &ContainerStatementSyntax::getType() const {
  return this->_type;
}

const std::unique_ptr<ExpressionSyntax> &
ContainerStatementSyntax::getContainerExpressionRef() const {
  return this->_containerExpression;
}
