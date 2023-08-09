
#include "VariableExpressionSyntax.h"

VariableExpressionSyntax::VariableExpressionSyntax(
    LiteralExpressionSyntax<std::any> *identifierExpression) {
  this->identifierExpression = identifierExpression;
}

SyntaxKindUtils::SyntaxKind VariableExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::VariableExpression;
}

LiteralExpressionSyntax<std::any> *VariableExpressionSyntax::getIdentifier() {
  return this->identifierExpression;
}

std::vector<SyntaxNode *> VariableExpressionSyntax::getChildren() {

  std::vector<SyntaxNode *> children = {identifierExpression};
  return children;
}

VariableExpressionSyntax::~VariableExpressionSyntax() {
  if (this->identifierExpression != nullptr) {
    delete this->identifierExpression;
    this->identifierExpression = nullptr;
  }
}
