#ifndef BOUDBREAKSTATEMENT_H
#define BOUDBREAKSTATEMENT_H

#include "../BoundStatement/BoundStatement.h"

class BoundBreakStatement : public BoundStatement {

public:
  BoundBreakStatement(const std::string &lineAndColumn);

public:
  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // BOUDBREAKSTATEMENT_H