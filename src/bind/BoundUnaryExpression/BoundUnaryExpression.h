#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"

class BoundUnaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundUnaryOperatorKind _op;
  std::unique_ptr<BoundExpression> _operand;

public:
  BoundUnaryExpression(std::string lineAndColumn,
                       BinderKindUtils::BoundUnaryOperatorKind op,
                       std::unique_ptr<BoundExpression> operand);

  const std::type_info &getType() override;

  std::unique_ptr<BoundExpression> getOperand();

  BinderKindUtils::BoundUnaryOperatorKind getOperator();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};