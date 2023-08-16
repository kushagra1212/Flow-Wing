#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundWhileStatement : public BoundStatement {
private:
  std::unique_ptr<BoundExpression> _condition;
  std::unique_ptr<BoundStatement> _body;

public:
  BoundWhileStatement(std::string lineAndColumn,
                      std::unique_ptr<BoundExpression> condition,
                      std::unique_ptr<BoundStatement> body);

  std::unique_ptr<BoundExpression> getCondition();
  std::unique_ptr<BoundStatement> getBody();

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;
  std::string getLineNumberAndColumn() override;

  std::unique_ptr<BoundExpression> &getConditionPtr();
  std::unique_ptr<BoundStatement> &getBodyPtr();
};