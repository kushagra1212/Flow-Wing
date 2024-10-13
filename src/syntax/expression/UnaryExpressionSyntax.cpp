#include "UnaryExpressionSyntax.h"

UnaryExpressionSyntax::UnaryExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> operatorToken,
    std::unique_ptr<ExpressionSyntax> operand) {
  this->_operatorToken = std::move(operatorToken);
  this->_operand = std::move(operand);
}

const SyntaxKindUtils::SyntaxKind UnaryExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::UnaryExpression;
}

const std::vector<SyntaxNode *> &UnaryExpressionSyntax::getChildren() {
  if (this->_children.size() == 0) {
    // Add children
    this->_children.push_back(this->_operatorToken.get());
    this->_children.push_back(this->_operand.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
UnaryExpressionSyntax::getSourceLocation() const {
  return this->_operatorToken->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
UnaryExpressionSyntax::getOperatorTokenRef() {
  return this->_operatorToken;
}

std::unique_ptr<ExpressionSyntax> &UnaryExpressionSyntax::getOperandRef() {
  return this->_operand;
}
