#include "CallExpressionSyntax.h"

CallExpressionSyntax::CallExpressionSyntax(
    LiteralExpressionSyntax<std::any> *identifier,
    SyntaxToken<std::any> *openParenthesisToken,
    std::vector<ExpressionSyntax *> arguments,
    SyntaxToken<std::any> *closeParenthesisToken) {
  this->identifier = identifier;
  this->openParenthesisToken = openParenthesisToken;
  this->arguments = arguments;
  this->closeParenthesisToken = closeParenthesisToken;
}

LiteralExpressionSyntax<std::any> *CallExpressionSyntax::getIdentifier() const {
  return identifier;
}

SyntaxToken<std::any> *CallExpressionSyntax::getOpenParenthesisToken() const {
  return openParenthesisToken;
}

std::vector<ExpressionSyntax *> CallExpressionSyntax::getArguments() const {
  return arguments;
}

SyntaxToken<std::any> *CallExpressionSyntax::getCloseParenthesisToken() const {
  return closeParenthesisToken;
}

SyntaxKindUtils::SyntaxKind CallExpressionSyntax::getKind() {
  return SyntaxKindUtils::CallExpression;
}

std::vector<SyntaxNode *> CallExpressionSyntax::getChildren() {
  std::vector<SyntaxNode *> children;
  children.push_back(identifier);
  children.push_back(openParenthesisToken);
  for (auto &argument : arguments) {
    children.push_back(argument);
  }
  children.push_back(closeParenthesisToken);
  return children;
}

CallExpressionSyntax::~CallExpressionSyntax() {
  delete identifier;
  delete openParenthesisToken;
  for (auto &argument : arguments) {
    delete argument;
  }
  delete closeParenthesisToken;
}
