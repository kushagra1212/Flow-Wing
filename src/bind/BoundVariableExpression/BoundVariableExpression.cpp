#include "BoundVariableExpression.h"

BoundVariableExpression::BoundVariableExpression(
    std::string lineAndColumn,
    std::unique_ptr<BoundExpression> identiferExpression) {
  this->_identiferExpression = std::move(identiferExpression);
  this->_lineAndColumn = lineAndColumn;

  this->_children.push_back(this->_identiferExpression.get());
}

const std::type_info &BoundVariableExpression::getType() {
  return this->_identiferExpression->getType();
}

std::unique_ptr<BoundExpression>
BoundVariableExpression::getIdentifierExpression() {
  return std::move(this->_identiferExpression);
}
BinderKindUtils::BoundNodeKind BoundVariableExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::VariableExpression;
}

std::vector<BoundNode *> BoundVariableExpression::getChildren() {
  return this->_children;
}

std::string BoundVariableExpression::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}

std::unique_ptr<BoundExpression> &
BoundVariableExpression::getIdentifierExpressionPtr() {
  return this->_identiferExpression;
}