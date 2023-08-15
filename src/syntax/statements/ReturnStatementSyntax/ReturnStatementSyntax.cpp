#include "ReturnStatementSyntax.h"

ReturnStatementSyntax::ReturnStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> returnKeyword,
    std::unique_ptr<ExpressionSyntax> expression) {
  this->_returnKeyword = std::move(returnKeyword);
  this->_expression = std::move(expression);

  // Add children

  _children.push_back(_returnKeyword.get());
  _children.push_back(_expression.get());
}

std::unique_ptr<SyntaxToken<std::any>>
ReturnStatementSyntax::getReturnKeyword() {

  return std::move(_returnKeyword);
}

std::unique_ptr<ExpressionSyntax> ReturnStatementSyntax::getExpression() {
  return std::move(_expression);
}

std::vector<SyntaxNode *> ReturnStatementSyntax::getChildren() {
  return this->_children;
}

SyntaxKindUtils::SyntaxKind ReturnStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ReturnStatement;
}

std::string ReturnStatementSyntax::getLineNumberAndColumn() {
  return _returnKeyword->getLineNumberAndColumn();
}
