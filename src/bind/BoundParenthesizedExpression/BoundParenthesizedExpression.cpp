#include "BoundParenthesizedExpression.h"

BoundParenthesizedExpression::BoundParenthesizedExpression(
    std::string lineAndColumn, std::unique_ptr<BoundExpression> expression) {
  this->_expression = std::move(expression);
  this->_lineAndColumn = lineAndColumn;

  this->_children.push_back(this->_expression.get());
}

const std::type_info &BoundParenthesizedExpression::getType() {
  return _expression->getType();
}

std::unique_ptr<BoundExpression> BoundParenthesizedExpression::getExpression() {
  return std::move(_expression);
}

BinderKindUtils::BoundNodeKind BoundParenthesizedExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::ParenthesizedExpression;
}

std::vector<BoundNode *> BoundParenthesizedExpression::getChildren() {
  return this->_children;
}

std::string BoundParenthesizedExpression::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}

std::unique_ptr<BoundExpression> &
BoundParenthesizedExpression::getExpressionPtr() {
  return this->_expression;
}