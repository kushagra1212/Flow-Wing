#include "BoundVariableExpression.h"

BoundVariableExpression::BoundVariableExpression(
    const std::string &lineAndColumn,
    std::shared_ptr<BoundExpression> identiferExpression) {
  this->identiferExpression = identiferExpression;
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundVariableExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::VariableExpression;
}

const std::type_info &BoundVariableExpression::getType() {
  return identiferExpression->getType();
}

std::shared_ptr<BoundExpression>
BoundVariableExpression::getIdentifierExpression() {
  return this->identiferExpression;
}

std::vector<std::shared_ptr<BoundNode>> BoundVariableExpression::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{this->identiferExpression};
}

std::string BoundVariableExpression::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
