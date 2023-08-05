#pragma once
#include "../../Common.h"
#include "../BinderKindUtils.h"
#include "../BoundStatement/BoundStatement.h"
class BoundBlockStatement : public BoundStatement {
private:
  std::vector<BoundStatement *> statements;
  bool global;

public:
  BoundBlockStatement(std::vector<BoundStatement *> statements, bool global);
  BoundBlockStatement(std::vector<BoundStatement *> statements);
  ~BoundBlockStatement();

public:
  BinderKindUtils::BoundNodeKind getKind();

public:
  std::vector<BoundStatement *> getStatements();

  bool getGlobal() const;

public:
  std::vector<BoundNode *> getChildren() override;
};