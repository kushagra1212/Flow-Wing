#include "ParenthesizedExpressionSyntax.h"

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(
    SyntaxToken<std::any> *openParenthesisToken, ExpressionSyntax *expression,
    SyntaxToken<std::any> *closeParenthesisToken) {
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

SyntaxToken<std::any> *
ParenthesizedExpressionSyntax::getOpenParenthesisToken() {
  return this->openParenthesisToken;
}

ExpressionSyntax *ParenthesizedExpressionSyntax::getExpression() {
  return this->expression;
}

SyntaxToken<std::any> *
ParenthesizedExpressionSyntax::getCloseParenthesisToken() {
  return this->closeParenthesisToken;
}

std::vector<SyntaxNode *> ParenthesizedExpressionSyntax::getChildren() {
  return children;
}

ParenthesizedExpressionSyntax::~ParenthesizedExpressionSyntax() {
  delete this->openParenthesisToken;
  delete this->expression;
  delete this->closeParenthesisToken;
}