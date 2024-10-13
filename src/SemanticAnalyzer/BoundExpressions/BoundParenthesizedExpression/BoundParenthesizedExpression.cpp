#include "BoundParenthesizedExpression.h"

BoundParenthesizedExpression::BoundParenthesizedExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> expression)
    : BoundExpression(location) {
  this->_expression = std::move(expression);

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

std::unique_ptr<BoundExpression> &
BoundParenthesizedExpression::getExpressionPtr() {
  return this->_expression;
}