#pragma once

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"

class BoundBinaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundBinaryOperatorKind _op;
  std::shared_ptr<BoundExpression> _left;
  std::shared_ptr<BoundExpression> _right;

public:
  BoundBinaryExpression(const std::string &lineAndColumn,
                        std::shared_ptr<BoundExpression> left,
                        BinderKindUtils::BoundBinaryOperatorKind op,
                        std::shared_ptr<BoundExpression> right);

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  const std::type_info &getType() override;

public:
  BinderKindUtils::BoundBinaryOperatorKind getOperator();

public:
  std::shared_ptr<BoundExpression> getLeft();

public:
  std::shared_ptr<BoundExpression> getRight();

public:
  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

public:
  std::string getLineNumberAndColumn() const override;
};
