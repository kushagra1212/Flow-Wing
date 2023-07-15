#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
class BoundAssignmentExpression : public BoundExpression {
private:
  BinderKindUtils::BoundBinaryOperatorKind op;
  BoundExpression *left;
  BoundExpression *right;

public:
  BoundAssignmentExpression(BoundExpression *left,
                            BinderKindUtils::BoundBinaryOperatorKind op,
                            BoundExpression *right);

public:
  BinderKindUtils::BoundNodeKind getKind();

public:
  const std::type_info &getType();

public:
  BinderKindUtils::BoundBinaryOperatorKind getOperator();

public:
  BoundExpression *getLeft();

public:
  BoundExpression *getRight();
};