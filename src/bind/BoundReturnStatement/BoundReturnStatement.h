#ifndef BOUNDRETURNSTATEMENT_H
#define BOUNDRETURNSTATEMENT_H

#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundReturnStatement : public BoundStatement {

private:
  BoundExpression *_expression;

public:
  BoundReturnStatement(BoundExpression *expression);

  ~BoundReturnStatement();

  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<BoundNode *> getChildren() override;

  BoundExpression *getReturnExpression() const;
};

#endif // BOUNDRETURNSTATEMENT_H