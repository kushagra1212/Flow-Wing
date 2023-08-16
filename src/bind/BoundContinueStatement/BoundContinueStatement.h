#ifndef BOUNDCONTINUESTATEMENT_H
#define BOUNDCONTINUESTATEMENT_H

#include "../BoundStatement/BoundStatement.h"

class BoundContinueStatement : public BoundStatement {

public:
  BoundContinueStatement(std::string lineAndColumn);

public:
  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};

#endif // BOUNDCONTINUESTATEMENT_H