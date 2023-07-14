#include "BoundLiteralExpression.h"

BoundLiteralExpression::BoundLiteralExpression(int value) {
  this->value = value;
}

BinderKindUtils::BoundNodeKind BoundLiteralExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::LiteralExpression;
}

const std::type_info &BoundLiteralExpression::getType() {
  const std::type_info &type1 = typeid(this->value);
  return type1;
}

int BoundLiteralExpression::getValue() { return value; }
