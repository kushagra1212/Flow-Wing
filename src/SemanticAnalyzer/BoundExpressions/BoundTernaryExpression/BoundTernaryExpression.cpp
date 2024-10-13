#include "BoundTernaryExpression.h"

BoundTernaryExpression::BoundTernaryExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> conditionExpression,
    std::unique_ptr<BoundExpression> trueExpression,
    std::unique_ptr<BoundExpression> falseExpression)
    : BoundExpression(location),
      _conditionExpression(std::move(conditionExpression)),
      _trueExpression(std::move(trueExpression)),
      _falseExpression(std::move(falseExpression)) {}

const std::type_info &BoundTernaryExpression::getType() { return typeid(void); }

BinderKindUtils::BoundNodeKind BoundTernaryExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundTernaryExpression;
}

std::vector<BoundNode *> BoundTernaryExpression::getChildren() {
  std::vector<BoundNode *> children;
  if (_children.empty()) {
    if (_conditionExpression)
      children.emplace_back(_conditionExpression.get());
    if (_trueExpression)
      children.emplace_back(_trueExpression.get());
    if (_falseExpression)
      children.emplace_back(_falseExpression.get());
  }

  return children;
}