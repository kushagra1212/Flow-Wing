#ifndef BOUNDCONTINUESTATEMENT_H
#define BOUNDCONTINUESTATEMENT_H

#include "../BoundStatement/BoundStatement.h"

class BoundContinueStatement : public BoundStatement {

public:
  BoundContinueStatement(const std::string &lineAndColumn);

public:
  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // BOUNDCONTINUESTATEMENT_H