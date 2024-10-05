#pragma once

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundTernaryExpression : public BoundExpression {
public:
  BoundTernaryExpression(const DiagnosticUtils::SourceLocation &location,
                         std::unique_ptr<BoundExpression> conditionExpression,
                         std::unique_ptr<BoundExpression> trueExpression,
                         std::unique_ptr<BoundExpression> falseExpression);

  inline const std::unique_ptr<BoundExpression> &
  getConditionExpressionRef() const {
    return _conditionExpression;
  }
  inline const std::unique_ptr<BoundExpression> &getTrueExpressionRef() const {
    return _trueExpression;
  }
  inline const std::unique_ptr<BoundExpression> &getFalseExpressionRef() const {
    return _falseExpression;
  }

  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

private:
  std::unique_ptr<BoundExpression> _conditionExpression;
  std::unique_ptr<BoundExpression> _trueExpression;
  std::unique_ptr<BoundExpression> _falseExpression;
};