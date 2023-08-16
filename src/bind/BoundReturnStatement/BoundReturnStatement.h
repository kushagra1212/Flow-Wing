#ifndef BOUNDRETURNSTATEMENT_H
#define BOUNDRETURNSTATEMENT_H

#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundReturnStatement : public BoundStatement {

private:
  std::unique_ptr<BoundExpression> _expression;

public:
  BoundReturnStatement(std::string lineAndColumn,
                       std::unique_ptr<BoundExpression> expression);

  std::unique_ptr<BoundExpression> getReturnExpression();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;

  std::unique_ptr<BoundExpression> &getReturnExpressionPtr();
};

#endif // BOUNDRETURNSTATEMENT_H