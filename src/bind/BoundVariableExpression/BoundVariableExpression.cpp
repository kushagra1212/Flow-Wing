#include "BoundVariableExpression.h"

BoundVariableExpression::BoundVariableExpression(
    BoundExpression *identiferExpression) {
  this->identiferExpression = identiferExpression;
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

BoundVariableExpression::~BoundVariableExpression() {
  delete this->identiferExpression;
}
