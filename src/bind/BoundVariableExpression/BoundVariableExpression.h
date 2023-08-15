#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
class BoundVariableExpression : public BoundExpression {
private:
  std::unique_ptr<BoundExpression> _identiferExpression;

public:
  BoundVariableExpression(std::string lineAndColumn,
                          std::unique_ptr<BoundExpression> identiferExpression);

  const std::type_info &getType() override;

  std::unique_ptr<BoundExpression> getIdentifierExpression();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};