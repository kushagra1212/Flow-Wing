#include "BoundAssignmentExpression.h"

BoundAssignmentExpression::BoundAssignmentExpression(
    std::string lineAndColumn, std::unique_ptr<BoundExpression> left,
    BinderKindUtils::BoundBinaryOperatorKind op,
    std::unique_ptr<BoundExpression> right) {
  this->_op = op;
  this->_left = std::move(left);
  this->_right = std::move(right);
  this->_lineAndColumn = lineAndColumn;

  _children.push_back(_left.get());
}

const std::type_info &BoundAssignmentExpression::getType() {
  return _right->getType();
}

BinderKindUtils::BoundBinaryOperatorKind
BoundAssignmentExpression::getOperator() {
  return _op;
}

std::unique_ptr<BoundExpression> BoundAssignmentExpression::getLeft() {
  return std::move(_left);
}

std::unique_ptr<BoundExpression> BoundAssignmentExpression::getRight() {
  return std::move(_right);
}
BinderKindUtils::BoundNodeKind BoundAssignmentExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::AssignmentExpression;
}

std::vector<BoundNode *> BoundAssignmentExpression::getChildren() {
  return this->_children;
}
std::string BoundAssignmentExpression::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}
