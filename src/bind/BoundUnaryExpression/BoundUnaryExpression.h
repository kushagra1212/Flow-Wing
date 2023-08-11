#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"

class BoundUnaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundUnaryOperatorKind op;
  BoundExpression *operand;

public:
  BoundUnaryExpression(const std::string &lineAndColumn,
                       BinderKindUtils::BoundUnaryOperatorKind op,
                       BoundExpression *operand);

  ~BoundUnaryExpression();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  const std::type_info &getType() override;

public:
  BinderKindUtils::BoundUnaryOperatorKind getOperator();

public:
  BoundExpression *getOperand();

public:
  std::vector<BoundNode *> getChildren() override;

public:
  std::string getLineNumberAndColumn() const override;
};