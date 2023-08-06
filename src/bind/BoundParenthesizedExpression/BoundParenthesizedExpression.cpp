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

std::vector<BoundNode *> BoundParenthesizedExpression::getChildren() {
  return std::vector<BoundNode *>{expression};
}

BoundParenthesizedExpression::~BoundParenthesizedExpression() {
  if (expression != nullptr) {
    delete expression;
    expression = nullptr;
  }
}
