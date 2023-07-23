#include "ForStatementSyntax.h"

ForStatementSyntax::ForStatementSyntax(
    VariableDeclarationSyntax *variableDeclaration,
    ExpressionSyntax *upperBound, BlockStatementSyntax *statement)
    : variableDeclaration(variableDeclaration), upperBound(upperBound),
      statement(statement) {}

BlockStatementSyntax *ForStatementSyntax::getStatement() const {
  return this->statement;
}

SyntaxKindUtils::SyntaxKind ForStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ForStatement;
}

std::vector<SyntaxNode *> ForStatementSyntax::getChildren() {
  return {this->variableDeclaration, (SyntaxNode *)this->statement};
}

ExpressionSyntax *ForStatementSyntax::getUpperBound() const {
  return this->upperBound;
}

VariableDeclarationSyntax *ForStatementSyntax::getVariableDeclaration() const {
  return this->variableDeclaration;
}