#include "IfStatementSyntax.h"

IfStatementSyntax::IfStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> ifKeyword,
    std::unique_ptr<ExpressionSyntax> condition,
    std::unique_ptr<BlockStatementSyntax> statement,
    std::unique_ptr<ElseClauseSyntax> elseClause) {
  this->ifKeyword = std::move(ifKeyword);
  this->condition = std::move(condition);
  this->statement = std::move(statement);
  this->elseClause = std::move(elseClause);

  // Add children

  _children.push_back(this->ifKeyword.get());
  _children.push_back(this->condition.get());
  _children.push_back(this->statement.get());
  if (this->elseClause != nullptr) {
    _children.push_back(this->elseClause.get());
  }
}

std::unique_ptr<SyntaxToken<std::any>> IfStatementSyntax::getIfKeyword() {
  return std::move(ifKeyword);
}

std::unique_ptr<ExpressionSyntax> IfStatementSyntax::getCondition() {
  return std::move(condition);
}

std::unique_ptr<BlockStatementSyntax> IfStatementSyntax::getStatement() {
  return std::move(statement);
}

std::unique_ptr<ElseClauseSyntax> IfStatementSyntax::getElseClause() {
  return std::move(elseClause);
}

SyntaxKindUtils::SyntaxKind IfStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::IfStatement;
}

std::string IfStatementSyntax::getLineNumberAndColumn() {
  return ifKeyword->getLineNumberAndColumn();
}

std::vector<SyntaxNode *> IfStatementSyntax::getChildren() {
  return this->_children;
}
