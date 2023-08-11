#pragma once
#include "../../Common.h"
#include "../BinderKindUtils.h"
#include "../BoundStatement/BoundStatement.h"
class BoundBlockStatement : public BoundStatement {
private:
  std::vector<BoundStatement *> statements;
  bool global;

public:
  BoundBlockStatement(const std::string &lineAndColumn,
                      std::vector<BoundStatement *> statements, bool global);
  BoundBlockStatement(const std::string &lineAndColumn,
                      std::vector<BoundStatement *> statements);
  ~BoundBlockStatement();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  std::vector<BoundStatement *> getStatements();

  bool getGlobal() const;

  std::string getLineNumberAndColumn() const override;

public:
  std::vector<BoundNode *> getChildren() override;
};