#include "UnaryExpressionSyntax.h"

UnaryExpressionSyntax::UnaryExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> operatorToken,
    std::unique_ptr<ExpressionSyntax> operand) {
  this->_operatorToken = std::move(operatorToken);
  this->_operand = std::move(operand);

  // Add children
  this->_children.push_back(this->_operatorToken.get());
  this->_children.push_back(this->_operand.get());
}

std::unique_ptr<SyntaxToken<std::any>>
UnaryExpressionSyntax::getOperatorToken() {
  return std::move(this->_operatorToken);
}

std::unique_ptr<ExpressionSyntax> UnaryExpressionSyntax::getOperand() {
  return std::move(this->_operand);
}

SyntaxKindUtils::SyntaxKind UnaryExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::UnaryExpression;
}

std::vector<SyntaxNode *> UnaryExpressionSyntax::getChildren() {
  return this->_children;
}

std::string UnaryExpressionSyntax::getLineNumberAndColumn() {
  return this->_operatorToken->getLineNumberAndColumn();
}
