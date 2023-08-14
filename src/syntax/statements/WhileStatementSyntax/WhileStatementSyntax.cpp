#include "WhileStatementSyntax.h"

WhileStatementSyntax::WhileStatementSyntax(
    std::shared_ptr<SyntaxToken<std::any>> whileKeyword,
    std::shared_ptr<ExpressionSyntax> condition,
    std::shared_ptr<BlockStatementSyntax> body)
    : _whileKeyword(whileKeyword), _condition(condition), _body(body) {}

SyntaxKindUtils::SyntaxKind WhileStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::WhileStatement;
}

std::vector<std::shared_ptr<SyntaxNode>> WhileStatementSyntax::getChildren() {
  std::vector<std::shared_ptr<SyntaxNode>> children = {
      _whileKeyword, _condition, (std::shared_ptr<SyntaxNode>)_body};
  return children;
}

std::shared_ptr<SyntaxToken<std::any>>
WhileStatementSyntax::getWhileKeyword() const {
  return _whileKeyword;
}

std::shared_ptr<ExpressionSyntax> WhileStatementSyntax::getCondition() const {
  return _condition;
}

std::shared_ptr<BlockStatementSyntax> WhileStatementSyntax::getBody() const {
  return _body;
}

std::string WhileStatementSyntax::getLineNumberAndColumn() const {
  return _whileKeyword->getLineNumberAndColumn();
}
