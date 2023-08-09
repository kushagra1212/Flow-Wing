#pragma once
#include "../../Common.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundExpressionStatement : public BoundStatement {

private:
  BoundExpression *expression;

public:
  BoundExpressionStatement(BoundExpression *expression);

  ~BoundExpressionStatement();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  BoundExpression *getExpression();

public:
  std::vector<BoundNode *> getChildren() override;
};
