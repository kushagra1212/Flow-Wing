#include "BoundParenthesizedExpression.h"

BoundParenthesizedExpression::BoundParenthesizedExpression(
    BoundExpression *expression) {
  this->expression = expression;
}

BinderKindUtils::BoundNodeKind BoundParenthesizedExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::ParenthesizedExpression;
}

const std::type_info &BoundParenthesizedExpression::getType() {
  return expression->getType();
}

BoundExpression *BoundParenthesizedExpression::getExpression() {
  return expression;
}

BoundParenthesizedExpression::~BoundParenthesizedExpression() {
  delete expression;
}