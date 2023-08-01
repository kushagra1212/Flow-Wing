#pragma once
#include "../../Common.h"
#include "../BinderKindUtils.h"
#include "../BoundStatement/BoundStatement.h"
class BoundBlockStatement : public BoundStatement {
private:
  std::vector<BoundStatement *> statements;

public:
  BoundBlockStatement(std::vector<BoundStatement *> statements);

  ~BoundBlockStatement();

public:
  BinderKindUtils::BoundNodeKind getKind();

public:
  std::vector<BoundStatement *> getStatements();
};