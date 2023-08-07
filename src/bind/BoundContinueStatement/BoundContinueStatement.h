#ifndef BOUNDCONTINUESTATEMENT_H
#define BOUNDCONTINUESTATEMENT_H

#include "../BoundStatement/BoundStatement.h"

class BoundContinueStatement : public BoundStatement {

public:
  BoundContinueStatement();

  ~BoundContinueStatement();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<BoundNode *> getChildren() override;
};

#endif // BOUNDCONTINUESTATEMENT_H