#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundVariableExpression : public BoundExpression,
                                public BoundSourceLocation {
private:
  std::unique_ptr<BoundExpression> _identiferExpression;

public:
  BoundVariableExpression(const DiagnosticUtils::SourceLocation &location,
                          std::unique_ptr<BoundExpression> identiferExpression);

  const std::type_info &getType() override;

  std::unique_ptr<BoundExpression> getIdentifierExpression();

  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getIdentifierExpressionPtr();
};