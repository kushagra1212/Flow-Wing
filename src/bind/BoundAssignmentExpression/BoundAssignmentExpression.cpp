#include "BoundAssignmentExpression.h"

BoundAssignmentExpression::BoundAssignmentExpression(
    const std::string &lineAndColumn, std::shared_ptr<BoundExpression> left,
    BinderKindUtils::BoundBinaryOperatorKind op,
    std::shared_ptr<BoundExpression> right) {
  this->op = op;
  this->_left = left;
  this->_right = right;
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundAssignmentExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::AssignmentExpression;
}

const std::type_info &BoundAssignmentExpression::getType() {
  return _right->getType();
}

BinderKindUtils::BoundBinaryOperatorKind
BoundAssignmentExpression::getOperator() {
  return op;
}

std::shared_ptr<BoundExpression> BoundAssignmentExpression::getLeft() {
  return _left;
}

std::shared_ptr<BoundExpression> BoundAssignmentExpression::getRight() {
  return _right;
}

std::vector<std::shared_ptr<BoundNode>>
BoundAssignmentExpression::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{_left, _right};
}
std::string BoundAssignmentExpression::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
