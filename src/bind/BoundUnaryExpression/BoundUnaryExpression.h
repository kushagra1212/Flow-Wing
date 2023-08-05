#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"

class BoundUnaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundUnaryOperatorKind op;
  BoundExpression *operand;

public:
  BoundUnaryExpression(BinderKindUtils::BoundUnaryOperatorKind op,
                       BoundExpression *operand);

  ~BoundUnaryExpression();

public:
  BinderKindUtils::BoundNodeKind getKind();

public:
  const std::type_info &getType();

public:
  BinderKindUtils::BoundUnaryOperatorKind getOperator();

public:
  BoundExpression *getOperand();

public:
  std::vector<BoundNode *> getChildren() override;
};