#ifndef GlobalStatementSyntax_H
#define GlobalStatementSyntax_H

#include "../../../Common.h"
#include "../../MemberSyntax.h"

#include "../StatementSyntax.h"
class GlobalStatementSyntax : public MemberSyntax {
private:
  StatementSyntax *_statement;

public:
  GlobalStatementSyntax(StatementSyntax *statement);

  ~GlobalStatementSyntax();

  StatementSyntax *getStatement() const;

  SyntaxKindUtils::SyntaxKind getKind() override;

  std::vector<SyntaxNode *> getChildren() override;
};

#endif // GlobalStatementSyntax_H