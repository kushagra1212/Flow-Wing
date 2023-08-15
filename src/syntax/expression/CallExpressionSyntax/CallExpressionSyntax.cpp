#include "CallExpressionSyntax.h"

CallExpressionSyntax::CallExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifier) {
  this->_identifier = std::move(identifier);
}

std::unique_ptr<LiteralExpressionSyntax<std::any>>
CallExpressionSyntax::getIdentifier() {
  return std::move(_identifier);
}

std::unique_ptr<SyntaxToken<std::any>>
CallExpressionSyntax::getOpenParenthesisToken() {
  return std::move(_openParenthesisToken);
}

std::vector<std::unique_ptr<ExpressionSyntax>> &
CallExpressionSyntax::getArguments() {
  return _arguments;
}

void CallExpressionSyntax::setOpenParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken) {
  this->_openParenthesisToken = std::move(openParenthesisToken);
}

void CallExpressionSyntax::addArgument(
    std::unique_ptr<ExpressionSyntax> argument) {
  this->_arguments.push_back(std::move(argument));
}

void CallExpressionSyntax::setCloseParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken) {
  this->_closeParenthesisToken = std::move(closeParenthesisToken);
}

std::unique_ptr<SyntaxToken<std::any>>
CallExpressionSyntax::getCloseParenthesisToken() {
  return std::move(_closeParenthesisToken);
}

SyntaxKindUtils::SyntaxKind CallExpressionSyntax::getKind() const {
  return SyntaxKindUtils::CallExpression;
}

std::vector<SyntaxNode *> CallExpressionSyntax::getChildren() {
  if (this->_children.size() == 0) {

    this->_children.push_back(_identifier.get());
    this->_children.push_back(_openParenthesisToken.get());
    for (const auto &argument : _arguments) {
      this->_children.push_back(argument.get());
    }
    this->_children.push_back(_closeParenthesisToken.get());
  }
  return this->_children;
}

std::string CallExpressionSyntax::getLineNumberAndColumn() {
  return _identifier->getLineNumberAndColumn();
}

std::unique_ptr<LiteralExpressionSyntax<std::any>> &
CallExpressionSyntax::getIdentifierPtr() {
  return _identifier;
}
std::unique_ptr<SyntaxToken<std::any>> &
CallExpressionSyntax::getOpenParenthesisTokenPtr() {
  return _openParenthesisToken;
}
std::unique_ptr<SyntaxToken<std::any>> &
CallExpressionSyntax::getCloseParenthesisTokenPtr() {
  return _closeParenthesisToken;
}