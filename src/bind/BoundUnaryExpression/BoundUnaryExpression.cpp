#include "BoundUnaryExpression.h"

BoundUnaryExpression::BoundUnaryExpression(

    std::string lineAndColumn, BinderKindUtils::BoundUnaryOperatorKind op,
    std::unique_ptr<BoundExpression> operand) {
  this->_op = op;
  this->_operand = std::move(operand);
  this->_lineAndColumn = lineAndColumn;

  this->_children.push_back(this->_operand.get());
}

const std::type_info &BoundUnaryExpression::getType() {
  return this->_operand->getType();
}

BinderKindUtils::BoundUnaryOperatorKind BoundUnaryExpression::getOperator() {
  return this->_op;
}

std::unique_ptr<BoundExpression> BoundUnaryExpression::getOperand() {
  return std::move(this->_operand);
}

BinderKindUtils::BoundNodeKind BoundUnaryExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::UnaryExpression;
}

std::vector<BoundNode *> BoundUnaryExpression::getChildren() {
  return this->_children;
}

std::string BoundUnaryExpression::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}

std::unique_ptr<BoundExpression> &BoundUnaryExpression::getOperandPtr() {
  return this->_operand;
}

BinderKindUtils::BoundUnaryOperatorKind &
BoundUnaryExpression::getOperatorPtr() {
  return this->_op;
}