#pragma once

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"

class BoundBinaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundBinaryOperatorKind op;
  BoundExpression *left;
  BoundExpression *right;

public:
  BoundBinaryExpression(BoundExpression *left,
                        BinderKindUtils::BoundBinaryOperatorKind op,
                        BoundExpression *right);

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  const std::type_info &getType() override;

public:
  BinderKindUtils::BoundBinaryOperatorKind getOperator();

public:
  BoundExpression *getLeft();

public:
  BoundExpression *getRight();
};