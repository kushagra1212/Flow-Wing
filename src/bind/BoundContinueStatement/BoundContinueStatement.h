#ifndef BOUNDCONTINUESTATEMENT_H
#define BOUNDCONTINUESTATEMENT_H

#include "../BoundStatement/BoundStatement.h"

class BoundContinueStatement : public BoundStatement {

public:
  BoundContinueStatement(const std::string &lineAndColumn);

  ~BoundContinueStatement();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // BOUNDCONTINUESTATEMENT_H