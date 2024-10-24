#include "ForStatementSyntax.h"

ForStatementSyntax::ForStatementSyntax(
    std::unique_ptr<StatementSyntax> initialization,
    std::unique_ptr<ExpressionSyntax> upperBound,
    std::unique_ptr<BlockStatementSyntax> statement,
    std::unique_ptr<ExpressionSyntax> stepExpression) {
  this->_initialization = std::move(initialization);
  this->_upperBound = std::move(upperBound);
  this->_statement = std::move(statement);
  this->_stepExpression = std::move(stepExpression);
}

std::unique_ptr<BlockStatementSyntax> ForStatementSyntax::getStatement() {
  return std::move(this->_statement);
}

std::unique_ptr<ExpressionSyntax> ForStatementSyntax::getUpperBound() {
  return std::move(this->_upperBound);
}

std::unique_ptr<ExpressionSyntax> ForStatementSyntax::getStepExpression() {
  return std::move(this->_stepExpression);
}

std::unique_ptr<StatementSyntax> ForStatementSyntax::getInitialization() {
  return std::move(this->_initialization);
}

const SyntaxKindUtils::SyntaxKind ForStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ForStatement;
}

const std::vector<SyntaxNode *> &ForStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_initialization.get());
    _children.push_back(_upperBound.get());
    if (_stepExpression)
      _children.push_back(_stepExpression.get());
    _children.push_back(_statement.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
ForStatementSyntax::getSourceLocation() const {
  return this->_initialization->getSourceLocation();
}

std::unique_ptr<BlockStatementSyntax> &ForStatementSyntax::getStatementRef() {
  return this->_statement;
}

std::unique_ptr<StatementSyntax> &ForStatementSyntax::getInitializationRef() {
  return this->_initialization;
}

std::unique_ptr<ExpressionSyntax> &ForStatementSyntax::getUpperBoundRef() {
  return this->_upperBound;
}

std::unique_ptr<ExpressionSyntax> &ForStatementSyntax::getStepExpressionRef() {
  return this->_stepExpression;
}