#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include <typeinfo>

class BoundParenthesizedExpression : public BoundExpression {
private:
  BoundExpression *expression;

public:
  BoundParenthesizedExpression(BoundExpression *expression);

  ~BoundParenthesizedExpression();

public:
public:
  BinderKindUtils::BoundNodeKind getKind();

public:
  const std::type_info &getType();

public:
  BoundExpression *getExpression();
};
