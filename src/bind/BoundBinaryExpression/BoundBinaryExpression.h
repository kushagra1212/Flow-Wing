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

  ~BoundBinaryExpression();

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

public:
  std::vector<BoundNode *> getChildren() override;
};
