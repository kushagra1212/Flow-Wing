#ifndef BREAKSTATEMENTSYNTAX_H
#define BREAKSTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

class BreakStatementSyntax : public StatementSyntax {
 private:
  std::unique_ptr<SyntaxToken<std::any>> _breakKeyword;

 public:
  BreakStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> breakKeyword);

  std::unique_ptr<SyntaxToken<std::any>> getBreakKeyword();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getBreakKeywordPtr();
};

#endif  // BREAKSTATEMENTSYNTAX_H
