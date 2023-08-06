#include "ForStatementSyntax.h"

ForStatementSyntax::ForStatementSyntax(StatementSyntax *initialization,
                                       ExpressionSyntax *upperBound,
                                       BlockStatementSyntax *statement)
    : initialization(initialization), upperBound(upperBound),
      statement(statement) {}

BlockStatementSyntax *ForStatementSyntax::getStatement() const {
  return this->statement;
}

SyntaxKindUtils::SyntaxKind ForStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ForStatement;
}

std::vector<SyntaxNode *> ForStatementSyntax::getChildren() {
  return {this->initialization, (SyntaxNode *)this->statement};
}

ExpressionSyntax *ForStatementSyntax::getUpperBound() const {
  return this->upperBound;
}

StatementSyntax *ForStatementSyntax::getInitialization() const {
  return this->initialization;
}

ForStatementSyntax::~ForStatementSyntax() {
  if (this->initialization != nullptr) {
    delete this->initialization;
    this->initialization = nullptr;
  }

  if (this->upperBound != nullptr) {
    delete this->upperBound;
    this->upperBound = nullptr;
  }

  if (this->statement != nullptr) {
    delete this->statement;
    this->statement = nullptr;
  }
}
