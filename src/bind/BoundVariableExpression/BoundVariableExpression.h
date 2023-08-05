#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
class BoundVariableExpression : public BoundExpression {
private:
  BoundExpression *identiferExpression;

public:
  BoundVariableExpression(BoundExpression *identiferExpression);

  ~BoundVariableExpression();

public:
  BinderKindUtils::BoundNodeKind getKind();

public:
  const std::type_info &getType();

public:
  BoundExpression *getIdentifierExpression();

public:
  std::vector<BoundNode *> getChildren() override;
};