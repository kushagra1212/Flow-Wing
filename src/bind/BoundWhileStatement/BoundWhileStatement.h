#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundWhileStatement : public BoundStatement {
private:
  BoundExpression *_condition;
  BoundStatement *_body;

public:
  BoundWhileStatement(BoundExpression *condition, BoundStatement *body);

  ~BoundWhileStatement();
  BinderKindUtils::BoundNodeKind getKind() override;
  BoundExpression *getCondition() const;
  BoundStatement *getBody() const;
};