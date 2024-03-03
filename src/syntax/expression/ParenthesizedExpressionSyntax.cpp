#include "ParenthesizedExpressionSyntax.h"

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken,
    std::unique_ptr<ExpressionSyntax> expression,
    std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken) {
  this->_openParenthesisToken = std::move(openParenthesisToken);
  this->_expression = std::move(expression);
  this->_closeParenthesisToken = std::move(closeParenthesisToken);
}

std::unique_ptr<SyntaxToken<std::any>>
ParenthesizedExpressionSyntax::getOpenParenthesisToken() {
  return std::move(this->_openParenthesisToken);
}

std::unique_ptr<ExpressionSyntax>
ParenthesizedExpressionSyntax::getExpression() {
  return std::move(this->_expression);
}

std::unique_ptr<SyntaxToken<std::any>>
ParenthesizedExpressionSyntax::getCloseParenthesisToken() {
  return std::move(this->_closeParenthesisToken);
}

const SyntaxKindUtils::SyntaxKind ParenthesizedExpressionSyntax::getKind()
    const {
  return SyntaxKindUtils::SyntaxKind::ParenthesizedExpression;
}
const std::vector<SyntaxNode *> &ParenthesizedExpressionSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    this->_children.push_back(_openParenthesisToken.get());
    this->_children.push_back(_expression.get());
    this->_children.push_back(_closeParenthesisToken.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
ParenthesizedExpressionSyntax::getSourceLocation() const {
  return this->_openParenthesisToken->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
ParenthesizedExpressionSyntax::getOpenParenthesisTokenPtr() {
  return this->_openParenthesisToken;
}

std::unique_ptr<ExpressionSyntax> &
ParenthesizedExpressionSyntax::getExpressionPtr() {
  return this->_expression;
}

std::unique_ptr<SyntaxToken<std::any>> &
ParenthesizedExpressionSyntax::getCloseParenthesisTokenPtr() {
  return this->_closeParenthesisToken;
}