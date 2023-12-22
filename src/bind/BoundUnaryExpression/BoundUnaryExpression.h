#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundUnaryExpression : public BoundExpression,
                             public BoundSourceLocation {
private:
  BinderKindUtils::BoundUnaryOperatorKind _op;
  std::unique_ptr<BoundExpression> _operand;

public:
  BoundUnaryExpression(const DiagnosticUtils::SourceLocation &location,
                       BinderKindUtils::BoundUnaryOperatorKind op,
                       std::unique_ptr<BoundExpression> operand);

  const std::type_info &getType() override;

  std::unique_ptr<BoundExpression> getOperand();

  BinderKindUtils::BoundUnaryOperatorKind getOperator();

  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getOperandPtr();

  BinderKindUtils::BoundUnaryOperatorKind &getOperatorPtr();
};