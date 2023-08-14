#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"

class BoundUnaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundUnaryOperatorKind op;
  std::shared_ptr<BoundExpression> operand;

public:
  BoundUnaryExpression(const std::string &lineAndColumn,
                       BinderKindUtils::BoundUnaryOperatorKind op,
                       std::shared_ptr<BoundExpression> operand);

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  const std::type_info &getType() override;

public:
  BinderKindUtils::BoundUnaryOperatorKind getOperator();

public:
  std::shared_ptr<BoundExpression> getOperand();

public:
  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

public:
  std::string getLineNumberAndColumn() const override;
};