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
  if (left != nullptr) {
    delete left;
    left = nullptr;
  }

  if (operatorToken != nullptr) {
    delete operatorToken;
    operatorToken = nullptr;
  }

  if (right != nullptr) {
    delete right;
    right = nullptr;
  }
}
