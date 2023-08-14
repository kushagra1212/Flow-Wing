#include "BoundUnaryExpression.h"

BoundUnaryExpression::BoundUnaryExpression(

    const std::string &lineAndColumn,
    BinderKindUtils::BoundUnaryOperatorKind op,
    std::shared_ptr<BoundExpression> operand) {
  this->op = op;
  this->operand = operand;
  this->_lineAndColumn = lineAndColumn;
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

std::shared_ptr<BoundExpression> BoundUnaryExpression::getOperand() {
  return operand;
}

std::vector<std::shared_ptr<BoundNode>> BoundUnaryExpression::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{operand};
}

std::string BoundUnaryExpression::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
