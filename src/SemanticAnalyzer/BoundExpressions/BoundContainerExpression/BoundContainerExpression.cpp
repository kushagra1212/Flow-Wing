#include "BoundContainerExpression.h"

BoundContainerExpression::BoundContainerExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundExpression(location) {}

/*
  OVERRIDES
*/

const std::type_info &BoundContainerExpression::getType() {
  return typeid(std::vector<std::unique_ptr<BoundExpression>>);
}

BinderKindUtils::BoundNodeKind BoundContainerExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundContainerExpression;
}

std::vector<BoundNode *> BoundContainerExpression::getChildren() {
  if (_children.size() > 0)
    return _children;

  for (auto &element : this->_elements)
    _children.push_back(element.get());

  return _children;
}

/*
  SETTERS
*/

void BoundContainerExpression::setElement(
    std::unique_ptr<BoundExpression> element) {
  this->_elements.push_back(std::move(element));
}

/*
  GETTERS
*/

auto BoundContainerExpression::getElementsRef() const
    -> const std::vector<std::unique_ptr<BoundExpression>> & {
  return this->_elements;
}