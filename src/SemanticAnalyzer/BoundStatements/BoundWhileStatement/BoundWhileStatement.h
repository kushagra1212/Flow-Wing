#pragma once

#include "../../BinderKindUtils.h"
#include "../../BoundExpressions/BoundExpression/BoundExpression.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"

class BoundWhileStatement : public BoundStatement, public BoundSourceLocation {
private:
  std::unique_ptr<BoundExpression> _condition;
  std::unique_ptr<BoundStatement> _body;

public:
  BoundWhileStatement(const DiagnosticUtils::SourceLocation &location,
                      std::unique_ptr<BoundExpression> condition,
                      std::unique_ptr<BoundStatement> body);

  std::unique_ptr<BoundExpression> getCondition();
  std::unique_ptr<BoundStatement> getBody();

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getConditionPtr();
  std::unique_ptr<BoundStatement> &getBodyPtr();
};