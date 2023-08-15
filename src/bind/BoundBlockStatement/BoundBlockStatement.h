#pragma once
#include "../../Common.h"
#include "../BinderKindUtils.h"
#include "../BoundNode.h"
#include "../BoundStatement/BoundStatement.h"
class BoundBlockStatement : public BoundStatement {
private:
  std::vector<std::unique_ptr<BoundStatement>> _statements;
  bool _global;

public:
  BoundBlockStatement(std::string lineAndColumn, bool global);
  BoundBlockStatement(std::string lineAndColumn);

  std::vector<std::unique_ptr<BoundStatement>> &getStatements();
  void addStatement(std::unique_ptr<BoundStatement> statement);
  bool getGlobal() const;

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::string getLineNumberAndColumn() override;

  std::vector<BoundNode *> getChildren();
};