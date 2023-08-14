#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include <typeinfo>

class BoundParenthesizedExpression : public BoundExpression {
private:
  std::shared_ptr<BoundExpression> expression;

public:
  BoundParenthesizedExpression(const std::string &lineAndColumn,
                               std::shared_ptr<BoundExpression> expression);

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  const std::type_info &getType() override;

public:
  std::shared_ptr<BoundExpression> getExpression();

public:
  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

public:
  std::string getLineNumberAndColumn() const override;
};
