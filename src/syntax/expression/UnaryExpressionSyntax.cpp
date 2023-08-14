#include "UnaryExpressionSyntax.h"

UnaryExpressionSyntax::UnaryExpressionSyntax(
    std::shared_ptr<SyntaxToken<std::any>> operatorToken,
    std::shared_ptr<ExpressionSyntax> operand) {

  this->_operatorToken = operatorToken;
  this->_operand = operand;
}

SyntaxKindUtils::SyntaxKind UnaryExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::UnaryExpression;
}

std::shared_ptr<SyntaxToken<std::any>>
UnaryExpressionSyntax::getOperatorToken() {
  return this->_operatorToken;
}

std::shared_ptr<ExpressionSyntax> UnaryExpressionSyntax::getOperand() {
  return this->_operand;
}

std::vector<std::shared_ptr<SyntaxNode>> UnaryExpressionSyntax::getChildren() {

  std::vector<std::shared_ptr<SyntaxNode>> children = {this->_operatorToken,
                                                       this->_operand};
  return children;
}

std::string UnaryExpressionSyntax::getLineNumberAndColumn() const {
  return this->_operatorToken->getLineNumberAndColumn();
}
