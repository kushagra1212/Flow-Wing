#pragma once
#include "../../Common.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundExpressionStatement : public BoundStatement {

private:
  std::shared_ptr<BoundExpression> _expression;

public:
  BoundExpressionStatement(const std::string &lineAndColumn,
                           std::shared_ptr<BoundExpression> expression);

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  std::shared_ptr<BoundExpression> getExpression();

public:
  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

public:
  std::string getLineNumberAndColumn() const override;
};
