#include "BoundAssignmentExpression.h"

BoundAssignmentExpression::BoundAssignmentExpression(
    const DiagnosticUtils::SourceLocation &location,
    BoundVariableDeclaration *variable, std::unique_ptr<BoundExpression> left,
    BinderKindUtils::BoundBinaryOperatorKind op,
    std::unique_ptr<BoundExpression> right, bool needDefaulInitilization)
    : BoundExpression(location), _op(op), _left(std::move(left)),
      _right(std::move(right)), _variable(std::move(variable)),
      _needDefaulInitilization(needDefaulInitilization) {}

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

BoundVariableDeclaration *BoundAssignmentExpression::getVariable() {
  return _variable;
}