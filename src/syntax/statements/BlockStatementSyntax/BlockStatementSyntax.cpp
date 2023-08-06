#include "BlockStatementSyntax.h"

BlockStatementSyntax::BlockStatementSyntax(
    SyntaxToken<std::any> *openBraceToken,
    std::vector<StatementSyntax *> statements,
    SyntaxToken<std::any> *closeBraceToken) {
  this->openBraceToken = openBraceToken;
  this->statements = statements;
  this->closeBraceToken = closeBraceToken;
}

SyntaxKindUtils::SyntaxKind BlockStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::BlockStatement;
}

std::vector<SyntaxNode *> BlockStatementSyntax::getChildren() {
  std::vector<SyntaxNode *> children;
  children.push_back(this->openBraceToken);
  for (int i = 0; i < this->statements.size(); i++) {
    children.push_back(this->statements[i]);
  }
  children.push_back(this->closeBraceToken);
  return children;
}

SyntaxToken<std::any> *BlockStatementSyntax::getOpenBraceToken() {
  return this->openBraceToken;
}

std::vector<StatementSyntax *> BlockStatementSyntax::getStatements() {
  return this->statements;
}

SyntaxToken<std::any> *BlockStatementSyntax::getCloseBraceToken() {
  return this->closeBraceToken;
}

BlockStatementSyntax::~BlockStatementSyntax() {
  if (this->openBraceToken != nullptr) {
    delete this->openBraceToken;
    this->openBraceToken = nullptr;
  }

  for (int i = 0; i < this->statements.size(); i++) {
    if (this->statements[i] != nullptr) {
      delete this->statements[i];
      this->statements[i] = nullptr;
    }
  }
  this->statements.clear();

  if (this->closeBraceToken != nullptr) {
    delete this->closeBraceToken;
    this->closeBraceToken = nullptr;
  }
}
