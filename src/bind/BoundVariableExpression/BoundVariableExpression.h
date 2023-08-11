#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
class BoundVariableExpression : public BoundExpression {
private:
  BoundExpression *identiferExpression;

public:
  BoundVariableExpression(const std::string &lineAndColumn,
                          BoundExpression *identiferExpression);

  ~BoundVariableExpression();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  const std::type_info &getType() override;

public:
  BoundExpression *getIdentifierExpression();

public:
  std::vector<BoundNode *> getChildren() override;

public:
  std::string getLineNumberAndColumn() const override;
};