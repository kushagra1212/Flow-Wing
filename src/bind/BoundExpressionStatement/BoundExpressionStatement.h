#pragma once
#include "../../Common.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundExpressionStatement : public BoundStatement {

private:
  std::unique_ptr<BoundExpression> _expression;

public:
  BoundExpressionStatement(std::string lineAndColumn,
                           std::unique_ptr<BoundExpression> expression);

  std::unique_ptr<BoundExpression> getExpression();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;

  std::unique_ptr<BoundExpression> &getExpressionPtr();
};
