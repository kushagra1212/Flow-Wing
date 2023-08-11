#ifndef CONTINUESTATEMENTSYNTAX_H
#define CONTINUESTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

class ContinueStatementSyntax : public StatementSyntax {
private:
  SyntaxToken<std::any> *_continueKeyword;

public:
  ContinueStatementSyntax(SyntaxToken<std::any> *continueKeyword);

  ~ContinueStatementSyntax();

  SyntaxToken<std::any> *getContinueKeyword() const;

  std::vector<SyntaxNode *> getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // CONTINUESTATEMENTSYNTAX_H