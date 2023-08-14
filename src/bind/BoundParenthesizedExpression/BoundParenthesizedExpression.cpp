#include "BoundParenthesizedExpression.h"

BoundParenthesizedExpression::BoundParenthesizedExpression(
    const std::string &lineAndColumn,
    std::shared_ptr<BoundExpression> expression) {
  this->expression = expression;
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundParenthesizedExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::ParenthesizedExpression;
}

const std::type_info &BoundParenthesizedExpression::getType() {
  return expression->getType();
}

std::shared_ptr<BoundExpression> BoundParenthesizedExpression::getExpression() {
  return expression;
}

std::vector<std::shared_ptr<BoundNode>>
BoundParenthesizedExpression::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{expression};
}

std::string BoundParenthesizedExpression::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
