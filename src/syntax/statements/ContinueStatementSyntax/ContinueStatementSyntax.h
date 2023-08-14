#ifndef CONTINUESTATEMENTSYNTAX_H
#define CONTINUESTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

class ContinueStatementSyntax : public StatementSyntax {
private:
  std::shared_ptr<SyntaxToken<std::any>> _continueKeyword;

public:
  ContinueStatementSyntax(
      std::shared_ptr<SyntaxToken<std::any>> continueKeyword);

  std::shared_ptr<SyntaxToken<std::any>> getContinueKeyword() const;

  std::vector<std::shared_ptr<SyntaxNode>> getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // CONTINUESTATEMENTSYNTAX_H