#include "BoundFillExpression.h"

BoundFillExpression::BoundFillExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

/*
 * OVERRIDES
 */

const std::type_info &BoundFillExpression::getType() { return typeid(this); }

BinderKindUtils::BoundNodeKind BoundFillExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundFillExpression;
}

std::vector<BoundNode *> BoundFillExpression::getChildren() {

  if (_children.empty()) {
    _children.push_back(_elementToFill.get());
    _children.push_back(_sizeToFill.get());
  }

  return _children;
}

/*
 * SETTERS
 */

void BoundFillExpression::setElementToFill(
    std::unique_ptr<BoundExpression> elementToFill) {
  _elementToFill = std::move(elementToFill);
}

void BoundFillExpression::setSizeToFill(
    std::unique_ptr<BoundExpression> sizeToFill) {
  _sizeToFill = std::move(sizeToFill);
}

/*
 * GETTERS
 */

auto BoundFillExpression::getElementToFillRef() const
    -> const std::unique_ptr<BoundExpression> & {
  return _elementToFill;
}

auto BoundFillExpression::getSizeToFillRef() const
    -> const std::unique_ptr<BoundExpression> & {
  return _sizeToFill;
}