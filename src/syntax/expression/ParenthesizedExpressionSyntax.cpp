#include "ParenthesizedExpressionSyntax.h"

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(
    std::shared_ptr<SyntaxToken<std::any>> openParenthesisToken,
    std::shared_ptr<ExpressionSyntax> expression,
    std::shared_ptr<SyntaxToken<std::any>> closeParenthesisToken) {
  this->_openParenthesisToken = openParenthesisToken;
  this->_expression = expression;
  this->_closeParenthesisToken = closeParenthesisToken;
}

SyntaxKindUtils::SyntaxKind ParenthesizedExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ParenthesizedExpression;
}

std::shared_ptr<SyntaxToken<std::any>>
ParenthesizedExpressionSyntax::getOpenParenthesisToken() {
  return this->_openParenthesisToken;
}

std::shared_ptr<ExpressionSyntax>
ParenthesizedExpressionSyntax::getExpression() {
  return this->_expression;
}

std::shared_ptr<SyntaxToken<std::any>>
ParenthesizedExpressionSyntax::getCloseParenthesisToken() {
  return this->_closeParenthesisToken;
}

std::vector<std::shared_ptr<SyntaxNode>>
ParenthesizedExpressionSyntax::getChildren() {

  std::vector<std::shared_ptr<SyntaxNode>> children = {
      this->_openParenthesisToken, this->_expression,
      this->_closeParenthesisToken};

  return children;
}

std::string ParenthesizedExpressionSyntax::getLineNumberAndColumn() const {
  return this->_openParenthesisToken->getLineNumberAndColumn();
}
