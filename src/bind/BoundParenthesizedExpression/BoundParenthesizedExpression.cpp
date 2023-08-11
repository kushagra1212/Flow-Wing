#include "BoundParenthesizedExpression.h"

BoundParenthesizedExpression::BoundParenthesizedExpression(
    const std::string &lineAndColumn, BoundExpression *expression) {
  this->expression = expression;
  this->_lineAndColumn = lineAndColumn;
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

std::string BoundParenthesizedExpression::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

BoundParenthesizedExpression::~BoundParenthesizedExpression() {
  if (expression != nullptr) {
    delete expression;
    expression = nullptr;
  }
}
