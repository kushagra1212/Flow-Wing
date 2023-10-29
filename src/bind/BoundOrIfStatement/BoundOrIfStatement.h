#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundOrIfStatement : public BoundStatement, public BoundSourceLocation {
private:
  std::unique_ptr<BoundExpression> _condition;
  std::unique_ptr<BoundStatement> _thenStatement;

public:
  BoundOrIfStatement(const DiagnosticUtils::SourceLocation &location,
                     std::unique_ptr<BoundExpression> condition,
                     std::unique_ptr<BoundStatement> thenStatement);

  std::unique_ptr<BoundExpression> getCondition();
  std::unique_ptr<BoundStatement> getThenStatement();

  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getConditionPtr();
  std::unique_ptr<BoundStatement> &getThenStatementPtr();
};