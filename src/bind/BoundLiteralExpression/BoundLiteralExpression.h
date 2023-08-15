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
  BoundLiteralExpression(std::string lineAndColumn, T value);

  const std::type_info &getType();

  T getValue();

  std::string getLineNumberAndColumn() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;
};