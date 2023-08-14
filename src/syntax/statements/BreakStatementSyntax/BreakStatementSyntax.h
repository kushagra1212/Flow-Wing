#ifndef BREAKSTATEMENTSYNTAX_H
#define BREAKSTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

class BreakStatementSyntax : public StatementSyntax {
private:
  std::shared_ptr<SyntaxToken<std::any>> _breakKeyword;

public:
  BreakStatementSyntax(std::shared_ptr<SyntaxToken<std::any>> breakKeyword);

  std::shared_ptr<SyntaxToken<std::any>> getBreakKeyword() const;

  std::vector<std::shared_ptr<SyntaxNode>> getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // BREAKSTATEMENTSYNTAX_H
