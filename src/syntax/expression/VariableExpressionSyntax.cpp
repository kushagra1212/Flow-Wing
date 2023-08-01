
#include "VariableExpressionSyntax.h"

VariableExpressionSyntax::VariableExpressionSyntax(
    ExpressionSyntax *identifierExpression) {
  this->identifierExpression = identifierExpression;
}

SyntaxKindUtils::SyntaxKind VariableExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::VariableExpression;
}

ExpressionSyntax *VariableExpressionSyntax::getIdentifier() {
  return this->identifierExpression;
}

std::vector<SyntaxNode *> VariableExpressionSyntax::getChildren() {

  std::vector<SyntaxNode *> children = {identifierExpression};
  return children;
}

VariableExpressionSyntax::~VariableExpressionSyntax() {
  delete this->identifierExpression;
}