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
std::vector<std::unique_ptr<SyntaxToken<std::any>>> &
CallExpressionSyntax::getSeparators() {
  return _separators;
}

void CallExpressionSyntax::setOpenParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken) {
  this->_openParenthesisToken = std::move(openParenthesisToken);
}

void CallExpressionSyntax::addArgument(
    std::unique_ptr<ExpressionSyntax> argument) {
  this->_arguments.push_back(std::move(argument));
}

void CallExpressionSyntax::addSeparator(
    std::unique_ptr<SyntaxToken<std::any>> separator) {
  this->_separators.push_back(std::move(separator));
}

void CallExpressionSyntax::setCloseParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken) {
  this->_closeParenthesisToken = std::move(closeParenthesisToken);
}

std::unique_ptr<SyntaxToken<std::any>>
CallExpressionSyntax::getCloseParenthesisToken() {
  return std::move(_closeParenthesisToken);
}

const SyntaxKindUtils::SyntaxKind CallExpressionSyntax::getKind() const {
  return SyntaxKindUtils::CallExpression;
}

const std::vector<SyntaxNode *> &CallExpressionSyntax::getChildren() {
  if (this->_children.size() == 0) {
    this->_children.push_back(_identifier.get());
    this->_children.push_back(_openParenthesisToken.get());

    for (int i = 0; i < _arguments.size(); i++) {
      this->_children.push_back(_arguments[i].get());
      if (i < _separators.size()) {
        this->_children.push_back(_separators[i].get());
      }
    }

    this->_children.push_back(_closeParenthesisToken.get());
  }
  return this->_children;
}

const DiagnosticUtils::SourceLocation CallExpressionSyntax::getSourceLocation()
    const {
  return this->_identifier->getSourceLocation();
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
