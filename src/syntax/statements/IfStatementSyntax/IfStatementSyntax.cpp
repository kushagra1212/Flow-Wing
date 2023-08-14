#include "IfStatementSyntax.h"

IfStatementSyntax::IfStatementSyntax(
    std::shared_ptr<SyntaxToken<std::any>> ifKeyword,
    std::shared_ptr<ExpressionSyntax> condition,
    std::shared_ptr<BlockStatementSyntax> statement,
    std::shared_ptr<ElseClauseSyntax> elseClause)
    : ifKeyword(ifKeyword), condition(condition), statement(statement),
      elseClause(elseClause) {}

std::shared_ptr<SyntaxToken<std::any>> IfStatementSyntax::getIfKeyword() const {
  return ifKeyword;
}

std::shared_ptr<ExpressionSyntax> IfStatementSyntax::getCondition() const {
  return condition;
}

std::shared_ptr<BlockStatementSyntax> IfStatementSyntax::getStatement() const {
  return statement;
}

std::shared_ptr<ElseClauseSyntax> IfStatementSyntax::getElseClause() const {
  return elseClause;
}

SyntaxKindUtils::SyntaxKind IfStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::IfStatement;
}

std::string IfStatementSyntax::getLineNumberAndColumn() const {
  return ifKeyword->getLineNumberAndColumn();
}

std::vector<std::shared_ptr<SyntaxNode>> IfStatementSyntax::getChildren() {
  std::vector<std::shared_ptr<SyntaxNode>> children = {
      ifKeyword, condition, (std::shared_ptr<SyntaxNode>)statement};
  if (elseClause != nullptr) {
    children.push_back(elseClause);
  }
  return children;
}
