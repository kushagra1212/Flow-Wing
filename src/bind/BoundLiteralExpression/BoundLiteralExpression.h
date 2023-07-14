#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include <typeinfo>

class BoundLiteralExpression : public BoundExpression {
private:
  int value;

public:
  BoundLiteralExpression(int value);

public:
  BinderKindUtils::BoundNodeKind getKind();

public:
  const std::type_info &getType();

public:
  int getValue();
};