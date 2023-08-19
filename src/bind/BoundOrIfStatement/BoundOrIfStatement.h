#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"
class BoundOrIfStatement : public BoundStatement {
private:
  std::unique_ptr<BoundExpression> _condition;
  std::unique_ptr<BoundStatement> _thenStatement;

public:
  BoundOrIfStatement(std::string lineAndColumn,
                     std::unique_ptr<BoundExpression> condition,
                     std::unique_ptr<BoundStatement> thenStatement);

  std::unique_ptr<BoundExpression> getCondition();
  std::unique_ptr<BoundStatement> getThenStatement();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::string getLineNumberAndColumn() override;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getConditionPtr();
  std::unique_ptr<BoundStatement> &getThenStatementPtr();
};