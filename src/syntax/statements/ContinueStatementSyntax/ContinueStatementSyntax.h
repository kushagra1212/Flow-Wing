#ifndef CONTINUESTATEMENTSYNTAX_H
#define CONTINUESTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

class ContinueStatementSyntax : public StatementSyntax {
 private:
  std::unique_ptr<SyntaxToken<std::any>> _continueKeyword;

 public:
  ContinueStatementSyntax(
      std::unique_ptr<SyntaxToken<std::any>> continueKeyword);

  std::unique_ptr<SyntaxToken<std::any>> getContinueKeyword();

  const std::vector<SyntaxNode *> &getChildren() override;
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getContinueKeywordPtr();
};

#endif  // CONTINUESTATEMENTSYNTAX_H