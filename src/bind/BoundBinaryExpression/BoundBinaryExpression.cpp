#include "BoundBinaryExpression.h"

BoundBinaryExpression::BoundBinaryExpression(
    BoundExpression *left, BinderKindUtils::BoundBinaryOperatorKind op,
    BoundExpression *right)
    : op(op), left(left), right(right) {}

BinderKindUtils::BoundNodeKind BoundBinaryExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::BinaryExpression;
}

const std::type_info &BoundBinaryExpression::getType() {
  return left->getType();
}

BinderKindUtils::BoundBinaryOperatorKind BoundBinaryExpression::getOperator() {
  return op;
}

BoundExpression *BoundBinaryExpression::getLeft() { return left; }

BoundExpression *BoundBinaryExpression::getRight() { return right; }
