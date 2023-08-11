#include "BoundVariableExpression.h"

BoundVariableExpression::BoundVariableExpression(
    const std::string &lineAndColumn, BoundExpression *identiferExpression) {
  this->identiferExpression = identiferExpression;
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundVariableExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::VariableExpression;
}

const std::type_info &BoundVariableExpression::getType() {
  return identiferExpression->getType();
}

BoundExpression *BoundVariableExpression::getIdentifierExpression() {
  return this->identiferExpression;
}

std::vector<BoundNode *> BoundVariableExpression::getChildren() {
  return std::vector<BoundNode *>{this->identiferExpression};
}

std::string BoundVariableExpression::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

BoundVariableExpression::~BoundVariableExpression() {
  if (this->identiferExpression != nullptr) {
    delete this->identiferExpression;
    this->identiferExpression = nullptr;
  }
}
