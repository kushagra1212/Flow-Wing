#include "BoundBinaryExpression.h"

BoundBinaryExpression::BoundBinaryExpression(
    const std::string &lineAndColumn, std::shared_ptr<BoundExpression> left,
    BinderKindUtils::BoundBinaryOperatorKind op,
    std::shared_ptr<BoundExpression> right)
    : _op(op), _left(left), _right(right) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundBinaryExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::BinaryExpression;
}

const std::type_info &BoundBinaryExpression::getType() {
  return _left->getType();
}

BinderKindUtils::BoundBinaryOperatorKind BoundBinaryExpression::getOperator() {
  return _op;
}

std::shared_ptr<BoundExpression> BoundBinaryExpression::getLeft() {
  return _left;
}

std::shared_ptr<BoundExpression> BoundBinaryExpression::getRight() {
  return _right;
}

std::vector<std::shared_ptr<BoundNode>> BoundBinaryExpression::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{_left, _right};
}

std::string BoundBinaryExpression::getLineNumberAndColumn() const {
  return _lineAndColumn;
}
