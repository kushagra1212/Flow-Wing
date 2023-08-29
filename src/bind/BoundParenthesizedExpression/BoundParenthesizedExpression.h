#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include <typeinfo>

class BoundParenthesizedExpression : public BoundExpression,
                                     public BoundSourceLocation {
private:
  std::unique_ptr<BoundExpression> _expression;

public:
  BoundParenthesizedExpression(const DiagnosticUtils::SourceLocation &location,
                               std::unique_ptr<BoundExpression> expression);

  const std::type_info &getType() override;

  std::unique_ptr<BoundExpression> getExpression();

  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getExpressionPtr();
};
