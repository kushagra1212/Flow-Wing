#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include <typeinfo>

class BoundParenthesizedExpression : public BoundExpression {
private:
  std::unique_ptr<BoundExpression> _expression;

public:
  BoundParenthesizedExpression(std::string lineAndColumn,
                               std::unique_ptr<BoundExpression> expression);

  const std::type_info &getType() override;

  std::unique_ptr<BoundExpression> getExpression();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};
