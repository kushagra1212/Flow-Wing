#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundWhileStatement : public BoundStatement {
private:
  std::shared_ptr<BoundExpression> _condition;
  std::shared_ptr<BoundStatement> _body;

public:
  BoundWhileStatement(const std::string &lineAndColumn,
                      std::shared_ptr<BoundExpression> condition,
                      std::shared_ptr<BoundStatement> body);

  BinderKindUtils::BoundNodeKind getKind() override;
  std::shared_ptr<BoundExpression> getCondition() const;
  std::shared_ptr<BoundStatement> getBody() const;
  std::vector<std::shared_ptr<BoundNode>> getChildren() override;
  std::string getLineNumberAndColumn() const override;
};