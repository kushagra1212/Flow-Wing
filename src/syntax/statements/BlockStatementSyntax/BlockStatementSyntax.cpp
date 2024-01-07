#include "BlockStatementSyntax.h"

BlockStatementSyntax::BlockStatementSyntax() {}

std::unique_ptr<SyntaxToken<std::any>>
BlockStatementSyntax::getOpenBraceToken() {
  return std::move(this->_openBraceToken);
}

std::vector<std::unique_ptr<StatementSyntax>> &
BlockStatementSyntax::getStatements() {
  return this->_statements;
}

std::unique_ptr<SyntaxToken<std::any>>
BlockStatementSyntax::getCloseBraceToken() {
  return std::move(this->_closeBraceToken);
}

void BlockStatementSyntax::addStatement(
    std::unique_ptr<StatementSyntax> statement) {
  this->_statements.push_back(std::move(statement));
}

void BlockStatementSyntax::setOpenBraceToken(
    std::unique_ptr<SyntaxToken<std::any>> openBraceToken) {
  this->_openBraceToken = std::move(openBraceToken);
}

void BlockStatementSyntax::setCloseBraceToken(
    std::unique_ptr<SyntaxToken<std::any>> closeBraceToken) {
  this->_closeBraceToken = std::move(closeBraceToken);
}

SyntaxKindUtils::SyntaxKind BlockStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BlockStatement;
}

std::vector<SyntaxNode *> BlockStatementSyntax::getChildren() {
  if (this->_children.size() == 0) {
    // Add children
    this->_children.push_back(this->_openBraceToken.get());
    for (const auto &statement : this->getStatements()) {
      this->_children.push_back(statement.get());
    }
    this->_children.push_back(this->_closeBraceToken.get());
  }
  return this->_children;
}

DiagnosticUtils::SourceLocation BlockStatementSyntax::getSourceLocation()
    const {
  return this->_openBraceToken->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
BlockStatementSyntax::getOpenBraceTokenPtr() {
  return this->_openBraceToken;
}

std::unique_ptr<SyntaxToken<std::any>> &
BlockStatementSyntax::getCloseBraceTokenPtr() {
  return this->_closeBraceToken;
}