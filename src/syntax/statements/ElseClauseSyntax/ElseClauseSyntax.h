#pragma once
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

class ElseClauseSyntax : public SyntaxNode {
private:
  SyntaxToken<std::any> *elseKeyword;
  StatementSyntax *statement;

public:
  ElseClauseSyntax(SyntaxToken<std::any> *elseKeyword,
                   StatementSyntax *statement);
  SyntaxToken<std::any> *getElseKeyword() const;
  StatementSyntax *getStatement() const;
  SyntaxKindUtils::SyntaxKind getKind() override;
  std::vector<SyntaxNode *> getChildren() override;
};
