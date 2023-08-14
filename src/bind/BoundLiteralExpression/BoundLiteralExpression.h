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
  BoundLiteralExpression(const std::string &lineAndColumn, T value);

public:
  BinderKindUtils::BoundNodeKind getKind();

public:
  const std::type_info &getType();

public:
  T getValue();

  std::string getLineNumberAndColumn() const override;

public:
  std::vector<std::shared_ptr<BoundNode>> getChildren() override;
};