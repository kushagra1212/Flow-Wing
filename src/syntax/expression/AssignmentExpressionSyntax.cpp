#include "AssignmentExpressionSyntax.h"

AssignmentExpressionSyntax::AssignmentExpressionSyntax(
    SyntaxToken *identifierToken, SyntaxToken *operatorToken,
    ExpressionSyntax *right)
    : identifierToken(identifierToken), operatorToken(operatorToken),
      right(right) {}

SyntaxKindUtils::SyntaxKind AssignmentExpressionSyntax::getKind() {

  return SyntaxKindUtils::SyntaxKind::AssignmentExpression;
}

std::vector<SyntaxNode *> AssignmentExpressionSyntax::getChildren() {

  std::vector<SyntaxNode *> children = {identifierToken, operatorToken, right};

  return children;
}

SyntaxToken *AssignmentExpressionSyntax::getIdentifierToken() {
  return identifierToken;
}

SyntaxToken *AssignmentExpressionSyntax::getOperatorToken() {
  return operatorToken;
}

ExpressionSyntax *AssignmentExpressionSyntax::getRight() { return right; }
