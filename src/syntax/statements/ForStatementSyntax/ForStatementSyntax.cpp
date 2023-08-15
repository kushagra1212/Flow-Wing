#include "ForStatementSyntax.h"

ForStatementSyntax::ForStatementSyntax(
    std::unique_ptr<StatementSyntax> initialization,
    std::unique_ptr<ExpressionSyntax> upperBound,
    std::unique_ptr<BlockStatementSyntax> statement) {
  this->_initialization = std::move(initialization);
  this->_upperBound = std::move(upperBound);
  this->_statement = std::move(statement);

  // Add children

  _children.push_back(_initialization.get());
  _children.push_back(_upperBound.get());
  _children.push_back(_statement.get());
}

std::unique_ptr<BlockStatementSyntax> ForStatementSyntax::getStatement() {
  return std::move(this->_statement);
}

std::unique_ptr<ExpressionSyntax> ForStatementSyntax::getUpperBound() {
  return std::move(this->_upperBound);
}

std::unique_ptr<StatementSyntax> ForStatementSyntax::getInitialization() {
  return std::move(this->_initialization);
}

SyntaxKindUtils::SyntaxKind ForStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ForStatement;
}

std::vector<SyntaxNode *> ForStatementSyntax::getChildren() {

  return this->_children;
}

std::string ForStatementSyntax::getLineNumberAndColumn() {
  return this->_initialization->getLineNumberAndColumn();
}
