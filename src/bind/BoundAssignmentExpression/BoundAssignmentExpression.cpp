#include "BoundAssignmentExpression.h"

BoundAssignmentExpression::BoundAssignmentExpression(
    const DiagnosticUtils::SourceLocation &location, Utils::Variable variable,
    std::unique_ptr<BoundExpression> left,
    BinderKindUtils::BoundBinaryOperatorKind op,
    std::unique_ptr<BoundExpression> right)
    : BoundSourceLocation(location) {
  this->_op = op;
  this->_left = std::move(left);
  this->_right = std::move(right);
  this->_variable = variable;
}

const std::type_info &BoundAssignmentExpression::getType() {
  return typeid(BoundAssignmentExpression);
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
  if (_children.size() == 0) {
    _children.push_back(_left.get());
    _children.push_back(_right.get());
  }

  return _children;
}

BinderKindUtils::BoundBinaryOperatorKind &
BoundAssignmentExpression::getOperatorPtr() {
  return this->_op;
}

std::unique_ptr<BoundExpression> &BoundAssignmentExpression::getLeftPtr() {
  return this->_left;
}

std::unique_ptr<BoundExpression> &BoundAssignmentExpression::getRightPtr() {
  return this->_right;
}

const Utils::Variable BoundAssignmentExpression::getVariable() const {
  return _variable;
}