#ifndef BOUNDRETURNSTATEMENT_H
#define BOUNDRETURNSTATEMENT_H

#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundReturnStatement : public BoundStatement {

private:
  std::shared_ptr<BoundExpression> _expression;

public:
  BoundReturnStatement(const std::string &lineAndColumn,
                       std::shared_ptr<BoundExpression> expression);

  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;

  std::shared_ptr<BoundExpression> getReturnExpression() const;
};

#endif // BOUNDRETURNSTATEMENT_H