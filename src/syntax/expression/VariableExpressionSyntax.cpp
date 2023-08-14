
#include "VariableExpressionSyntax.h"

VariableExpressionSyntax::VariableExpressionSyntax(
    std::shared_ptr<LiteralExpressionSyntax<std::any>> identifierExpression) {
  this->_identifierExpression = identifierExpression;
}

SyntaxKindUtils::SyntaxKind VariableExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::VariableExpression;
}

std::shared_ptr<LiteralExpressionSyntax<std::any>>
VariableExpressionSyntax::getIdentifier() {
  return this->_identifierExpression;
}

std::vector<std::shared_ptr<SyntaxNode>>
VariableExpressionSyntax::getChildren() {

  std::vector<std::shared_ptr<SyntaxNode>> children = {_identifierExpression};
  return children;
}

std::string VariableExpressionSyntax::getLineNumberAndColumn() const {
  return this->_identifierExpression->getLineNumberAndColumn();
}
