#pragma once
#include "../../Common.h"
#include "../BinderKindUtils.h"
#include "../BoundStatement/BoundStatement.h"
class BoundBlockStatement : public BoundStatement {
private:
  std::vector<std::shared_ptr<BoundStatement>> _statements;
  bool _global;

public:
  BoundBlockStatement(const std::string &lineAndColumn,
                      std::vector<std::shared_ptr<BoundStatement>> statements,
                      bool global);
  BoundBlockStatement(const std::string &lineAndColumn,
                      std::vector<std::shared_ptr<BoundStatement>> statements);

public:
  BinderKindUtils::BoundNodeKind getKind() override;

public:
  std::vector<std::shared_ptr<BoundStatement>> getStatements();

  bool getGlobal() const;

  std::string getLineNumberAndColumn() const override;

public:
  std::vector<std::shared_ptr<BoundNode>> getChildren() override;
};