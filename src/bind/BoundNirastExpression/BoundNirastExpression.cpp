#include "BoundNirastExpression.h"

BoundNirastExpression::BoundNirastExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundExpression(location) {}

BinderKindUtils::BoundNodeKind BoundNirastExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundNirastExpression;
}

std::vector<BoundNode *> BoundNirastExpression::getChildren() {
  if (_children.size() > 0) {
    return _children;
  }

  if (_nirastExpression)
    _children.push_back(this->_nirastExpression.get());

  return _children;
}
