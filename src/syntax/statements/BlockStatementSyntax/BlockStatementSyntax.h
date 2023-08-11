#pragma once
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"
class BlockStatementSyntax : public StatementSyntax {
private:
  SyntaxToken<std::any> *openBraceToken;
  std::vector<StatementSyntax *> statements;
  SyntaxToken<std::any> *closeBraceToken;

public:
  BlockStatementSyntax(SyntaxToken<std::any> *openBraceToken,
                       std::vector<StatementSyntax *> statements,
                       SyntaxToken<std::any> *closeBraceToken);

  ~BlockStatementSyntax();
  SyntaxKindUtils::SyntaxKind getKind();

  std::vector<SyntaxNode *> getChildren();

  SyntaxToken<std::any> *getOpenBraceToken();

  std::vector<StatementSyntax *> getStatements();

  SyntaxToken<std::any> *getCloseBraceToken();

  std::string getLineNumberAndColumn() const override;
};