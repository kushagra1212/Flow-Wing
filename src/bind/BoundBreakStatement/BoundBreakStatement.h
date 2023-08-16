#ifndef BOUDBREAKSTATEMENT_H
#define BOUDBREAKSTATEMENT_H

#include "../BoundStatement/BoundStatement.h"

class BoundBreakStatement : public BoundStatement {

public:
  BoundBreakStatement(std::string lineAndColumn);

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};

#endif // BOUDBREAKSTATEMENT_H