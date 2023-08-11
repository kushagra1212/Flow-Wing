#include "CallExpressionSyntax.h"

CallExpressionSyntax::CallExpressionSyntax(
    LiteralExpressionSyntax<std::any> *identifier,
    SyntaxToken<std::any> *openParenthesisToken,
    std::vector<ExpressionSyntax *> arguments,
    SyntaxToken<std::any> *closeParenthesisToken) {
  this->_identifier = identifier;
  this->_openParenthesisToken = openParenthesisToken;
  this->_arguments = arguments;
  this->_closeParenthesisToken = closeParenthesisToken;
}

LiteralExpressionSyntax<std::any> *CallExpressionSyntax::getIdentifier() const {
  return _identifier;
}

SyntaxToken<std::any> *CallExpressionSyntax::getOpenParenthesisToken() const {
  return _openParenthesisToken;
}

std::vector<ExpressionSyntax *> CallExpressionSyntax::getArguments() const {
  return _arguments;
}

SyntaxToken<std::any> *CallExpressionSyntax::getCloseParenthesisToken() const {
  return _closeParenthesisToken;
}

SyntaxKindUtils::SyntaxKind CallExpressionSyntax::getKind() {
  return SyntaxKindUtils::CallExpression;
}

std::vector<SyntaxNode *> CallExpressionSyntax::getChildren() {
  std::vector<SyntaxNode *> children;
  children.push_back(_identifier);
  children.push_back(_openParenthesisToken);
  for (auto &argument : _arguments) {
    children.push_back(argument);
  }
  children.push_back(_closeParenthesisToken);
  return children;
}

std::string CallExpressionSyntax::getLineNumberAndColumn() const {
  return _identifier->getLineNumberAndColumn();
}

CallExpressionSyntax::~CallExpressionSyntax() {
  if (_identifier != nullptr) {
    delete _identifier;
    _identifier = nullptr;
  }

  if (_openParenthesisToken != nullptr) {
    delete _openParenthesisToken;
    _openParenthesisToken = nullptr;
  }

  for (auto &argument : _arguments) {
    if (argument != nullptr) {
      delete argument;
      argument = nullptr;
    }
  }
  _arguments.clear();

  if (_closeParenthesisToken != nullptr) {
    delete _closeParenthesisToken;
    _closeParenthesisToken = nullptr;
  }
}
