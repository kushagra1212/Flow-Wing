#ifndef BOUNDRETURNSTATEMENT_H
#define BOUNDRETURNSTATEMENT_H

#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundReturnStatement : public BoundStatement {

private:
  BoundExpression *_expression;

public:
  BoundReturnStatement(const std::string &lineAndColumn,
                       BoundExpression *expression);

  ~BoundReturnStatement();

  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() const override;

  BoundExpression *getReturnExpression() const;
};

#endif // BOUNDRETURNSTATEMENT_H