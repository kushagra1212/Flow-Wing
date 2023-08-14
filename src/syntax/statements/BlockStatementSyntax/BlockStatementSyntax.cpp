#include "BlockStatementSyntax.h"

BlockStatementSyntax::BlockStatementSyntax(
    std::shared_ptr<SyntaxToken<std::any>> openBraceToken,
    std::vector<std::shared_ptr<StatementSyntax>> statements,
    std::shared_ptr<SyntaxToken<std::any>> closeBraceToken) {
  this->_openBraceToken = openBraceToken;
  this->_statements = statements;
  this->_closeBraceToken = closeBraceToken;
}

SyntaxKindUtils::SyntaxKind BlockStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::BlockStatement;
}

std::vector<std::shared_ptr<SyntaxNode>> BlockStatementSyntax::getChildren() {
  std::vector<std::shared_ptr<SyntaxNode>> children;
  children.push_back(this->_openBraceToken);
  for (int i = 0; i < this->_statements.size(); i++) {
    children.push_back(this->_statements[i]);
  }
  children.push_back(this->_closeBraceToken);
  return children;
}

std::shared_ptr<SyntaxToken<std::any>>
BlockStatementSyntax::getOpenBraceToken() {
  return this->_openBraceToken;
}

std::vector<std::shared_ptr<StatementSyntax>>
BlockStatementSyntax::getStatements() {
  return this->_statements;
}

std::shared_ptr<SyntaxToken<std::any>>
BlockStatementSyntax::getCloseBraceToken() {
  return this->_closeBraceToken;
}

std::string BlockStatementSyntax::getLineNumberAndColumn() const {
  return this->_openBraceToken->getLineNumberAndColumn();
}
