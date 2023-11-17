#include "BoundContainerStatement.h"

BoundContainerStatement::BoundContainerStatement(
    const DiagnosticUtils::SourceLocation &location, Utils::type type,
    std::unique_ptr<BoundLiteralExpression<std::any>> identifierExpression)
    : BoundSourceLocation(location) {
  this->_type = type;
  this->_identifierExpression = std::move(identifierExpression);
}

BinderKindUtils::BoundNodeKind BoundContainerStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ContainerStatement;
}

std::vector<BoundNode *> BoundContainerStatement::getChildren() {
  if (_children.size() == 0) {
    _children.push_back(_identifierExpression.get());
  }

  return _children;
}

void BoundContainerStatement::addEntryExpression(
    std::unique_ptr<BoundExpression> entryExpression) {
  this->_entryExpressions.push_back(std::move(entryExpression));
}

std::unique_ptr<BoundLiteralExpression<std::any>> &
BoundContainerStatement::getIdentifierExpression() {
  return this->_identifierExpression;
}
std::vector<std::unique_ptr<BoundExpression>> &
BoundContainerStatement::getEntryExpressions() {
  return this->_entryExpressions;
}
Utils::type BoundContainerStatement::getContainerType() const {
  return this->_type;
}
