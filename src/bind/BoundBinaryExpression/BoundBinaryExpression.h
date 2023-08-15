#pragma once

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"

class BoundBinaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundBinaryOperatorKind _op;
  std::unique_ptr<BoundExpression> _left;
  std::unique_ptr<BoundExpression> _right;

public:
  BoundBinaryExpression(std::string lineAndColumn,
                        std::unique_ptr<BoundExpression> left,
                        BinderKindUtils::BoundBinaryOperatorKind op,
                        std::unique_ptr<BoundExpression> right);

  const std::type_info &getType() override;

  BinderKindUtils::BoundBinaryOperatorKind getOperator();

  std::unique_ptr<BoundExpression> getLeft();

  std::unique_ptr<BoundExpression> getRight();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};
