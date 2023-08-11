#include "BoundAssignmentExpression.h"

BoundAssignmentExpression::BoundAssignmentExpression(
    const std::string &lineAndColumn, BoundExpression *left,
    BinderKindUtils::BoundBinaryOperatorKind op, BoundExpression *right) {
  this->op = op;
  this->left = left;
  this->right = right;
  this->_lineAndColumn = lineAndColumn;
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

std::vector<BoundNode *> BoundAssignmentExpression::getChildren() {
  return std::vector<BoundNode *>{left, right};
}
std::string BoundAssignmentExpression::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

BoundAssignmentExpression::~BoundAssignmentExpression() {
  if (left != nullptr) {
    delete left;
    left = nullptr;
  }

  if (right != nullptr) {
    delete right;
    right = nullptr;
  }
}
