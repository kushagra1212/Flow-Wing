#ifndef BREAKSTATEMENTSYNTAX_H
#define BREAKSTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

class BreakStatementSyntax : public StatementSyntax {
private:
  SyntaxToken<std::any> *_breakKeyword;

public:
  BreakStatementSyntax(SyntaxToken<std::any> *breakKeyword);

  ~BreakStatementSyntax();

  SyntaxToken<std::any> *getBreakKeyword() const;

  std::vector<SyntaxNode *> getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // BREAKSTATEMENTSYNTAX_H
