#include "BoundBinaryExpression.h"

BoundBinaryExpression::BoundBinaryExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> left,
    BinderKindUtils::BoundBinaryOperatorKind op,
    std::unique_ptr<BoundExpression> right)
    : BoundExpression(location) {
  this->_op = op;

  this->_left = std::move(left);
  this->_right = std::move(right);

  // TODO:

  _children.push_back(_left.get());
  _children.push_back(_right.get());
}

const std::type_info &BoundBinaryExpression::getType() {
  return typeid(BoundBinaryExpression);
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

BinderKindUtils::BoundBinaryOperatorKind &
BoundBinaryExpression::getOperatorPtr() {
  return _op;
}

std::unique_ptr<BoundExpression> &BoundBinaryExpression::getLeftPtr() {
  return _left;
}

std::unique_ptr<BoundExpression> &BoundBinaryExpression::getRightPtr() {
  return _right;
}