#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundOrIfStatement/BoundOrIfStatement.h"
#include "../BoundStatement/BoundStatement.h"
class BoundIfStatement : public BoundStatement {
private:
  std::unique_ptr<BoundExpression> _condition;
  std::unique_ptr<BoundStatement> _thenStatement;
  std::unique_ptr<BoundStatement> _elseStatement;

  std::vector<std::unique_ptr<BoundOrIfStatement>> _orIfStatements;

public:
  BoundIfStatement(std::string lineAndColumn);

  std::unique_ptr<BoundExpression> getCondition();
  std::unique_ptr<BoundStatement> getThenStatement();
  std::unique_ptr<BoundStatement> getElseStatement();

  void addCondition(std::unique_ptr<BoundExpression> condition);
  void addThenStatement(std::unique_ptr<BoundStatement> thenStatement);
  void addOrIfStatement(std::unique_ptr<BoundOrIfStatement> orIfStatement);
  void addElseStatement(std::unique_ptr<BoundStatement> elseStatement);

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::string getLineNumberAndColumn() override;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getConditionPtr();
  std::unique_ptr<BoundStatement> &getThenStatementPtr();
  std::unique_ptr<BoundStatement> &getElseStatementPtr();
  std::vector<std::unique_ptr<BoundOrIfStatement>> &getOrIfStatementsPtr();
};