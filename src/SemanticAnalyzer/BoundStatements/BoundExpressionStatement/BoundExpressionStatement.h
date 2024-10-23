#pragma once

#include "../../../common/Common.h"
#include "../../BinderKindUtils.h"
#include "../../BoundExpressions/BoundExpression/BoundExpression.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"

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
