#ifndef EMPTY_STATEMENT_SYNTAX_H
#define EMPTY_STATEMENT_SYNTAX_H

#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

class EmptyStatementSyntax : public StatementSyntax {
 public:
  EmptyStatementSyntax();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;
};

#endif  // EMPTY_STATEMENT_SYNTAX_H