#include "ParenthesizedExpressionSyntax.h"

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(
    SyntaxToken *openParenthesisToken, ExpressionSyntax *expression,
    SyntaxToken *closeParenthesisToken) {
  this->openParenthesisToken = openParenthesisToken;
  this->expression = expression;
  this->closeParenthesisToken = closeParenthesisToken;
  children.push_back(this->openParenthesisToken);
  children.push_back(this->expression);
  children.push_back(this->closeParenthesisToken);
}

SyntaxKindUtils::SyntaxKind ParenthesizedExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ParenthesizedExpression;
}

SyntaxToken *ParenthesizedExpressionSyntax::getOpenParenthesisToken() {
  return this->openParenthesisToken;
}

ExpressionSyntax *ParenthesizedExpressionSyntax::getExpression() {
  return this->expression;
}

SyntaxToken *ParenthesizedExpressionSyntax::getCloseParenthesisToken() {
  return this->closeParenthesisToken;
}

std::vector<SyntaxNode *> ParenthesizedExpressionSyntax::getChildren() {
  return children;
}