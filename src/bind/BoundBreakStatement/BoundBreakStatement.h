#ifndef BOUDBREAKSTATEMENT_H
#define BOUDBREAKSTATEMENT_H

#include "../BoundStatement/BoundStatement.h"

class BoundBreakStatement : public BoundStatement {

public:
  BoundBreakStatement(const std::string &lineAndColumn);

  ~BoundBreakStatement();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // BOUDBREAKSTATEMENT_H