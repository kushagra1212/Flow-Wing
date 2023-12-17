#include "BracketedExpressionSyntax.h"

/*
    OVERIDES
*/

SyntaxKindUtils::SyntaxKind BracketedExpressionSyntax::getKind() const {
  return SyntaxKindUtils::BracketedExpression;
}

std::vector<SyntaxNode *> BracketedExpressionSyntax::getChildren() {

  if (_children.empty()) {
    _children.push_back(_expression.get());
  }

  return _children;
}

DiagnosticUtils::SourceLocation
BracketedExpressionSyntax::getSourceLocation() const {
  return _expression->getSourceLocation();
}

/*
    SETTERS
*/

auto BracketedExpressionSyntax::setExpression(
    std::unique_ptr<ExpressionSyntax> expression) -> void {
  _expression = std::move(expression);
}

/*
    GETTERS
*/

auto BracketedExpressionSyntax::getExpressionRef() const
    -> const std::unique_ptr<ExpressionSyntax> & {
  return _expression;
}
