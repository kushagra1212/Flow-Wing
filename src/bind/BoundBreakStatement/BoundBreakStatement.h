#ifndef BOUDBREAKSTATEMENT_H
#define BOUDBREAKSTATEMENT_H

#include "../BoundStatement/BoundStatement.h"

class BoundBreakStatement : public BoundStatement {

public:
  BoundBreakStatement();

  ~BoundBreakStatement();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<BoundNode *> getChildren() override;
};

#endif // BOUDBREAKSTATEMENT_H