#include "BoundBinaryExpression.h"

BoundBinaryExpression::BoundBinaryExpression(
    std::string lineAndColumn, std::unique_ptr<BoundExpression> left,
    BinderKindUtils::BoundBinaryOperatorKind op,
    std::unique_ptr<BoundExpression> right) {
  this->_op = op;

  this->_left = std::move(left);
  this->_right = std::move(right);

  this->_lineAndColumn = lineAndColumn;

  // TODO:

  _children.push_back(_left.get());
  _children.push_back(_right.get());
}

const std::type_info &BoundBinaryExpression::getType() {
  return _left->getType();
}

BinderKindUtils::BoundBinaryOperatorKind BoundBinaryExpression::getOperator() {
  return _op;
}

std::unique_ptr<BoundExpression> BoundBinaryExpression::getLeft() {
  return std::move(_left);
}

std::unique_ptr<BoundExpression> BoundBinaryExpression::getRight() {
  return std::move(_right);
}
BinderKindUtils::BoundNodeKind BoundBinaryExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BinaryExpression;
}
std::vector<BoundNode *> BoundBinaryExpression::getChildren() {
  return _children;
}

std::string BoundBinaryExpression::getLineNumberAndColumn() {
  return _lineAndColumn;
}
