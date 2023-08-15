#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"
class BoundIfStatement : public BoundStatement {
private:
  std::unique_ptr<BoundExpression> _condition;
  std::unique_ptr<BoundStatement> _thenStatement;
  std::unique_ptr<BoundStatement> _elseStatement;

public:
  BoundIfStatement(std::string lineAndColumn,
                   std::unique_ptr<BoundExpression> condition,
                   std::unique_ptr<BoundStatement> thenStatement,
                   std::unique_ptr<BoundStatement> elseStatement);

  std::unique_ptr<BoundExpression> getCondition();
  std::unique_ptr<BoundStatement> getThenStatement();
  std::unique_ptr<BoundStatement> getElseStatement();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::string getLineNumberAndColumn() override;

  std::vector<BoundNode *> getChildren() override;
};