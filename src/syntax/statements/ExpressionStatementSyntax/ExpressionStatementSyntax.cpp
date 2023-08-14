#include "ExpressionStatementSyntax.h"

ExpressionStatementSyntax::ExpressionStatementSyntax(
    std::shared_ptr<ExpressionSyntax> expression) {
  this->_expression = expression;
}

SyntaxKindUtils::SyntaxKind ExpressionStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ExpressionStatement;
}

std::vector<std::shared_ptr<SyntaxNode>>
ExpressionStatementSyntax::getChildren() {
  return std::vector<std::shared_ptr<SyntaxNode>>{this->_expression};
}

std::shared_ptr<ExpressionSyntax> ExpressionStatementSyntax::getExpression() {
  return this->_expression;
}

std::string ExpressionStatementSyntax::getLineNumberAndColumn() const {
  return this->_expression->getLineNumberAndColumn();
}
