#include "ForStatementSyntax.h"

ForStatementSyntax::ForStatementSyntax(
    std::shared_ptr<StatementSyntax> initialization,
    std::shared_ptr<ExpressionSyntax> upperBound,
    std::shared_ptr<BlockStatementSyntax> statement)
    : _initialization(initialization), _upperBound(upperBound),
      _statement(statement) {}

std::shared_ptr<BlockStatementSyntax> ForStatementSyntax::getStatement() const {
  return this->_statement;
}

SyntaxKindUtils::SyntaxKind ForStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ForStatement;
}

std::vector<std::shared_ptr<SyntaxNode>> ForStatementSyntax::getChildren() {
  return {this->_initialization, this->_statement};
}

std::shared_ptr<ExpressionSyntax> ForStatementSyntax::getUpperBound() const {
  return this->_upperBound;
}

std::shared_ptr<StatementSyntax> ForStatementSyntax::getInitialization() const {
  return this->_initialization;
}

std::string ForStatementSyntax::getLineNumberAndColumn() const {
  return this->_initialization->getLineNumberAndColumn();
}
