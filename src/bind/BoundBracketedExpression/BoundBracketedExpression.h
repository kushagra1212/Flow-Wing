#ifndef __FLOWWING_BOUND_BRACKETED_EXPRESSION_H__
#define __FLOWWING_BOUND_BRACKETED_EXPRESSION_H__

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundBracketedExpression : public BoundExpression {
 private:
  std::unique_ptr<BoundExpression> _expression;

 public:
  BoundBracketedExpression(const DiagnosticUtils::SourceLocation &location);
  // OVERRIDES
  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  // SETTERS
  void setExpression(std::unique_ptr<BoundExpression> expression);

  // GETTERS
  auto getExpressionRef() const -> const std::unique_ptr<BoundExpression> &;
};

#endif  // __FLOWWING_BOUND_BRACKETED_EXPRESSION_H__