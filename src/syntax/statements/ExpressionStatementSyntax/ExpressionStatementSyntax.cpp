#include "ExpressionStatementSyntax.h"

ExpressionStatementSyntax::ExpressionStatementSyntax(
    ExpressionSyntax *expression) {
  this->expression = expression;
}

SyntaxKindUtils::SyntaxKind ExpressionStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ExpressionStatement;
}

std::vector<SyntaxNode *> ExpressionStatementSyntax::getChildren() {
  return std::vector<SyntaxNode *>{this->expression};
}

ExpressionSyntax *ExpressionStatementSyntax::getExpression() {
  return this->expression;
}