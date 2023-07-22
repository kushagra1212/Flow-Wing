#include "WhileStatementSyntax.h"

WhileStatementSyntax::WhileStatementSyntax(SyntaxToken<std::any> *whileKeyword,
                                           ExpressionSyntax *condition,
                                           BlockStatementSyntax *body)
    : _whileKeyword(whileKeyword), _condition(condition), _body(body) {}

SyntaxKindUtils::SyntaxKind WhileStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::WhileStatement;
}

std::vector<SyntaxNode *> WhileStatementSyntax::getChildren() {
  std::vector<SyntaxNode *> children = {_whileKeyword, _condition,
                                        (SyntaxNode *)_body};
  return children;
}

SyntaxToken<std::any> *WhileStatementSyntax::getWhileKeyword() const {
  return _whileKeyword;
}

ExpressionSyntax *WhileStatementSyntax::getCondition() const {
  return _condition;
}

BlockStatementSyntax *WhileStatementSyntax::getBody() const { return _body; }
