#include "BoundAssignmentExpression.h"

BoundAssignmentExpression::BoundAssignmentExpression(
    BoundExpression *left, BinderKindUtils::BoundBinaryOperatorKind op,
    BoundExpression *right) {
  this->op = op;
  this->left = left;
  this->right = right;
}

BinderKindUtils::BoundNodeKind BoundAssignmentExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::AssignmentExpression;
}

const std::type_info &BoundAssignmentExpression::getType() {
  return right->getType();
}

BinderKindUtils::BoundBinaryOperatorKind
BoundAssignmentExpression::getOperator() {
  return op;
}

BoundExpression *BoundAssignmentExpression::getLeft() { return left; }

BoundExpression *BoundAssignmentExpression::getRight() { return right; }
