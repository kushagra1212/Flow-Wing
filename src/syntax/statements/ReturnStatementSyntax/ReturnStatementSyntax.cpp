#include "ReturnStatementSyntax.h"

ReturnStatementSyntax::ReturnStatementSyntax(
    SyntaxToken<std::any> *returnKeyword, ExpressionSyntax *expression)
    : _returnKeyword(returnKeyword), _expression(expression) {}

SyntaxToken<std::any> *ReturnStatementSyntax::getReturnKeyword() const {

  return _returnKeyword;
}

ExpressionSyntax *ReturnStatementSyntax::getExpression() const {
  return _expression;
}

std::vector<SyntaxNode *> ReturnStatementSyntax::getChildren() {
  return {_returnKeyword, (SyntaxNode *)_expression};
}

SyntaxKindUtils::SyntaxKind ReturnStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ReturnStatement;
}

std::string ReturnStatementSyntax::getLineNumberAndColumn() const {
  return _returnKeyword->getLineNumberAndColumn();
}

ReturnStatementSyntax::~ReturnStatementSyntax() {
  if (_returnKeyword != nullptr) {
    delete _returnKeyword;
    _returnKeyword = nullptr;
  }

  if (_expression != nullptr) {
    delete _expression;
    _expression = nullptr;
  }
}
