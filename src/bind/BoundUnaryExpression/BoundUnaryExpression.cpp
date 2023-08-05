#include "BoundUnaryExpression.h"

BoundUnaryExpression::BoundUnaryExpression(
    BinderKindUtils::BoundUnaryOperatorKind op, BoundExpression *operand) {
  this->op = op;
  this->operand = operand;
}

BinderKindUtils::BoundNodeKind BoundUnaryExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::UnaryExpression;
}

const std::type_info &BoundUnaryExpression::getType() {
  return operand->getType();
}

BinderKindUtils::BoundUnaryOperatorKind BoundUnaryExpression::getOperator() {
  return op;
}

BoundExpression *BoundUnaryExpression::getOperand() { return operand; }

std::vector<BoundNode *> BoundUnaryExpression::getChildren() {
  return std::vector<BoundNode *>{operand};
}

BoundUnaryExpression::~BoundUnaryExpression() { delete operand; }
