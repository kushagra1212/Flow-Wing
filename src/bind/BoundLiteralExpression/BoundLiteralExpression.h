#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include <any>
#include <iostream>
#include <typeinfo>
template <typename T> class BoundLiteralExpression : public BoundExpression {
private:
  T value;

public:
  BoundLiteralExpression(T value);

  ~BoundLiteralExpression();

public:
  BinderKindUtils::BoundNodeKind getKind();

public:
  const std::type_info &getType();

public:
  T getValue();

public:
  std::vector<BoundNode *> getChildren() override;
};