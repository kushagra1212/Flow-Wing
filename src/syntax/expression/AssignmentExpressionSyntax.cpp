#include "AssignmentExpressionSyntax.h"

AssignmentExpressionSyntax::AssignmentExpressionSyntax(
    ExpressionSyntax *left, SyntaxToken *operatorToken, ExpressionSyntax *right)
    : left(left), operatorToken(operatorToken), right(right) {}

SyntaxKindUtils::SyntaxKind AssignmentExpressionSyntax::getKind() {

  return SyntaxKindUtils::SyntaxKind::AssignmentExpression;
}

std::vector<SyntaxNode *> AssignmentExpressionSyntax::getChildren() {

  std::vector<SyntaxNode *> children = {left, operatorToken, right};

  return children;
}

SyntaxToken *AssignmentExpressionSyntax::getOperatorToken() {
  return operatorToken;
}

ExpressionSyntax *AssignmentExpressionSyntax::getRight() { return right; }

ExpressionSyntax *AssignmentExpressionSyntax::getLeft() { return left; }