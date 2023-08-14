#include "ReturnStatementSyntax.h"

ReturnStatementSyntax::ReturnStatementSyntax(
    std::shared_ptr<SyntaxToken<std::any>> returnKeyword,
    std::shared_ptr<ExpressionSyntax> expression)
    : _returnKeyword(returnKeyword), _expression(expression) {}

std::shared_ptr<SyntaxToken<std::any>>
ReturnStatementSyntax::getReturnKeyword() const {

  return _returnKeyword;
}

std::shared_ptr<ExpressionSyntax> ReturnStatementSyntax::getExpression() const {
  return _expression;
}

std::vector<std::shared_ptr<SyntaxNode>> ReturnStatementSyntax::getChildren() {
  return {_returnKeyword, (std::shared_ptr<SyntaxNode>)_expression};
}

SyntaxKindUtils::SyntaxKind ReturnStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ReturnStatement;
}

std::string ReturnStatementSyntax::getLineNumberAndColumn() const {
  return _returnKeyword->getLineNumberAndColumn();
}
