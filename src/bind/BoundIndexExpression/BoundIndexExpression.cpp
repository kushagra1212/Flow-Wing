#include "BoundIndexExpression.h"

BoundIndexExpression::BoundIndexExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundLiteralExpression<std::any>> boundIdentifierExpression,
    std::unique_ptr<BoundLiteralExpression<std::any>> boundIndexExpression)
    : BoundSourceLocation(location) {

  _boundIdentifierExpression = std::move(boundIdentifierExpression);
  _boundIndexExpression = std::move(boundIndexExpression);
}

const std::type_info &BoundIndexExpression::getType() {
  return _boundIdentifierExpression->getType();
}

BinderKindUtils::BoundNodeKind BoundIndexExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::IndexExpression;
}

std::vector<BoundNode *> BoundIndexExpression::getChildren() {
  if (_children.size() == 0) {
    _children.push_back(_boundIdentifierExpression.get());
    _children.push_back(_boundIndexExpression.get());
  }

  return _children;
}

std::unique_ptr<BoundLiteralExpression<std::any>> &
BoundIndexExpression::getBoundIdentifierExpression() {
  return _boundIdentifierExpression;
}

std::unique_ptr<BoundLiteralExpression<std::any>> &
BoundIndexExpression::getBoundIndexExpression() {
  return _boundIndexExpression;
}