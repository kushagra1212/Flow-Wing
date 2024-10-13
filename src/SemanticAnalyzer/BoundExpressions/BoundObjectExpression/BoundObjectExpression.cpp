#include "BoundObjectExpression.h"

BoundObjectExpression::BoundObjectExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundExpression(location) {}

BinderKindUtils::BoundNodeKind BoundObjectExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundObjectExpression;
}

std::vector<BoundNode *> BoundObjectExpression::getChildren() {
  if (_children.size() > 0) {
    return _children;
  }

  for (auto &keyTypePair : _key_value_pairs) {
    _children.push_back(keyTypePair.first.get());
    _children.push_back(keyTypePair.second.get());
  }

  return _children;
}
