#include "BoundBinaryExpression.h"

BoundBinaryExpression::BoundBinaryExpression(
    const std::string &lineAndColumn, BoundExpression *left,
    BinderKindUtils::BoundBinaryOperatorKind op, BoundExpression *right)
    : op(op), left(left), right(right) {
  this->_lineAndColumn = lineAndColumn;
}

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

std::vector<BoundNode *> BoundBinaryExpression::getChildren() {
  return std::vector<BoundNode *>{left, right};
}

std::string BoundBinaryExpression::getLineNumberAndColumn() const {
  return _lineAndColumn;
}

BoundBinaryExpression::~BoundBinaryExpression() {
  if (left != nullptr) {
    delete left;
    left = nullptr;
  }

  if (right != nullptr) {
    delete right;
    right = nullptr;
  }
}
