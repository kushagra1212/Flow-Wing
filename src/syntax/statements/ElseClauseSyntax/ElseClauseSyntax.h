#pragma once
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../StatementSyntax.h"
class ElseClauseSyntax : public SyntaxNode {
private:
  SyntaxToken<std::any> *elseKeyword;
  BlockStatementSyntax *statement;

public:
  ElseClauseSyntax(SyntaxToken<std::any> *elseKeyword,
                   BlockStatementSyntax *statement);
  SyntaxToken<std::any> *getElseKeyword() const;
  BlockStatementSyntax *getStatement() const;
  SyntaxKindUtils::SyntaxKind getKind() override;
  std::vector<SyntaxNode *> getChildren() override;
};
