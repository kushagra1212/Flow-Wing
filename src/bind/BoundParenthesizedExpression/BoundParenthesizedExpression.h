#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include <typeinfo>

class BoundParenthesizedExpression : public BoundExpression {
private:
  BoundExpression *expression;

public:
  BoundParenthesizedExpression(const std::string &lineAndColumn,
                               BoundExpression *expression);

  ~BoundParenthesizedExpression();

public:
public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  const std::type_info &getType() override;

public:
  BoundExpression *getExpression();

public:
  std::vector<BoundNode *> getChildren() override;

public:
  std::string getLineNumberAndColumn() const override;
};
