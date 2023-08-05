#include "AssignmentExpressionSyntax.h"

AssignmentExpressionSyntax::AssignmentExpressionSyntax(
    LiteralExpressionSyntax<std::any> *left,
    SyntaxToken<std::any> *operatorToken, ExpressionSyntax *right)
    : left(left), operatorToken(operatorToken), right(right) {}

SyntaxKindUtils::SyntaxKind AssignmentExpressionSyntax::getKind() {

  return SyntaxKindUtils::SyntaxKind::AssignmentExpression;
}

std::vector<SyntaxNode *> AssignmentExpressionSyntax::getChildren() {

  std::vector<SyntaxNode *> children = {left, operatorToken, right};

  return children;
}

SyntaxToken<std::any> *AssignmentExpressionSyntax::getOperatorToken() {
  return operatorToken;
}

ExpressionSyntax *AssignmentExpressionSyntax::getRight() { return right; }

LiteralExpressionSyntax<std::any> *AssignmentExpressionSyntax::getLeft() {
  return left;
}

AssignmentExpressionSyntax::~AssignmentExpressionSyntax() {
  delete left;
  delete operatorToken;
  delete right;
}