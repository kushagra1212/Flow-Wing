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
  BoundIfStatement(std::string const &lineAndColumn, BoundExpression *condition,
                   BoundStatement *thenStatement,
                   BoundStatement *elseStatement);

  ~BoundIfStatement();
  BinderKindUtils::BoundNodeKind getKind() override;
  BoundExpression *getCondition() const;
  BoundStatement *getThenStatement() const;
  BoundStatement *getElseStatement() const;

  std::string getLineNumberAndColumn() const override;

public:
  std::vector<BoundNode *> getChildren() override;
};