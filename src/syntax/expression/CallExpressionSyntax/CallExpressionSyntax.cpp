#include "CallExpressionSyntax.h"

CallExpressionSyntax::CallExpressionSyntax(
    std::shared_ptr<LiteralExpressionSyntax<std::any>> identifier,
    std::shared_ptr<SyntaxToken<std::any>> openParenthesisToken,
    std::vector<std::shared_ptr<ExpressionSyntax>> arguments,
    std::shared_ptr<SyntaxToken<std::any>> closeParenthesisToken) {
  this->_identifier = identifier;
  this->_openParenthesisToken = openParenthesisToken;
  this->_arguments = arguments;
  this->_closeParenthesisToken = closeParenthesisToken;
}

std::shared_ptr<LiteralExpressionSyntax<std::any>>
CallExpressionSyntax::getIdentifier() const {
  return _identifier;
}

std::shared_ptr<SyntaxToken<std::any>>
CallExpressionSyntax::getOpenParenthesisToken() const {
  return _openParenthesisToken;
}

std::vector<std::shared_ptr<ExpressionSyntax>>
CallExpressionSyntax::getArguments() const {
  return _arguments;
}

std::shared_ptr<SyntaxToken<std::any>>
CallExpressionSyntax::getCloseParenthesisToken() const {
  return _closeParenthesisToken;
}

SyntaxKindUtils::SyntaxKind CallExpressionSyntax::getKind() {
  return SyntaxKindUtils::CallExpression;
}

std::vector<std::shared_ptr<SyntaxNode>> CallExpressionSyntax::getChildren() {
  std::vector<std::shared_ptr<SyntaxNode>> children;
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
