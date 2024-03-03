#include "ReturnStatementSyntax.h"

ReturnStatementSyntax::ReturnStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> returnKeyword,
    std::unique_ptr<ExpressionSyntax> expression) {
  this->_returnKeyword = std::move(returnKeyword);
  this->_expression = std::move(expression);
}

std::unique_ptr<SyntaxToken<std::any>>
ReturnStatementSyntax::getReturnKeyword() {
  return std::move(_returnKeyword);
}

std::unique_ptr<ExpressionSyntax> ReturnStatementSyntax::getExpression() {
  return std::move(_expression);
}

const std::vector<SyntaxNode *> &ReturnStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children

    _children.push_back(_returnKeyword.get());
    _children.push_back(_expression.get());
  }

  return this->_children;
}

const SyntaxKindUtils::SyntaxKind ReturnStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ReturnStatement;
}

const DiagnosticUtils::SourceLocation ReturnStatementSyntax::getSourceLocation()
    const {
  return _returnKeyword->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
ReturnStatementSyntax::getReturnKeywordPtr() {
  return _returnKeyword;
}
std::unique_ptr<ExpressionSyntax> &ReturnStatementSyntax::getExpressionPtr() {
  return _expression;
}