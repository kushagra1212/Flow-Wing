#include "BoundArrayTypeExpression.h"

BoundArrayTypeExpression::BoundArrayTypeExpression(
    const DiagnosticUtils::SourceLocation &location, Utils::type type)
    : BoundTypeExpression(location, type) {}

std::vector<BoundNode *> BoundArrayTypeExpression::getChildren() {
  if (this->_children.empty()) {
    for (auto &dimension : this->_dimensions) {
      this->_children.push_back(dimension.get());
    }
  }

  return this->_children;
}

BinderKindUtils::BoundNodeKind BoundArrayTypeExpression::getKind() const {
  return BinderKindUtils::BoundArrayTypeExpression;
}