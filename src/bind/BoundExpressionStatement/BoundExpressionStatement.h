#pragma once
#include "../../Common.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundExpressionStatement : public BoundStatement,
                                 public BoundSourceLocation {
 private:
  std::unique_ptr<BoundExpression> _expression;

 public:
  BoundExpressionStatement(const DiagnosticUtils::SourceLocation &location,
                           std::unique_ptr<BoundExpression> expression);

  std::unique_ptr<BoundExpression> getExpression();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getExpressionPtr();
};
