#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"
class BoundIfStatement : public BoundStatement {
private:
  std::shared_ptr<BoundExpression> _condition;
  std::shared_ptr<BoundStatement> _thenStatement;
  std::shared_ptr<BoundStatement> _elseStatement;

public:
  BoundIfStatement(std::string const &lineAndColumn,
                   std::shared_ptr<BoundExpression> condition,
                   std::shared_ptr<BoundStatement> thenStatement,
                   std::shared_ptr<BoundStatement> elseStatement);

  BinderKindUtils::BoundNodeKind getKind() override;
  std::shared_ptr<BoundExpression> getCondition() const;
  std::shared_ptr<BoundStatement> getThenStatement() const;
  std::shared_ptr<BoundStatement> getElseStatement() const;

  std::string getLineNumberAndColumn() const override;

public:
  std::vector<std::shared_ptr<BoundNode>> getChildren() override;
};