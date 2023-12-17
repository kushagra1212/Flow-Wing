#include "BoundBracketedExpression.h"

BoundBracketedExpression::BoundBracketedExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}
/*
    OVERRIDES
*/

const std::type_info &BoundBracketedExpression::getType() {
  return typeid(BoundBracketedExpression);
}

BinderKindUtils::BoundNodeKind BoundBracketedExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundBracketedExpression;
}

std::vector<BoundNode *> BoundBracketedExpression::getChildren() {

  if (_children.size() > 0)
    return _children;

  _children.push_back(_expression.get());
  return _children;
}

/*
    SETTERS
*/

void BoundBracketedExpression::setExpression(
    std::unique_ptr<BoundExpression> expression) {
  _expression = std::move(expression);
}

/*
    GETTERS
*/

auto BoundBracketedExpression::getExpressionRef() const
    -> const std::unique_ptr<BoundExpression> & {
  return _expression;
}
