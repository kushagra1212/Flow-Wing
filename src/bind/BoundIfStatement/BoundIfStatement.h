#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"
class BoundIfStatement : public BoundStatement {
private:
  BoundExpression *_condition;
  BoundStatement *_thenStatement;
  BoundStatement *_elseStatement;

public:
  BoundIfStatement(BoundExpression *condition, BoundStatement *thenStatement,
                   BoundStatement *elseStatement);

  ~BoundIfStatement();
  BinderKindUtils::BoundNodeKind getKind() override;
  BoundExpression *getCondition() const;
  BoundStatement *getThenStatement() const;
  BoundStatement *getElseStatement() const;
};