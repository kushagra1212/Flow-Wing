#ifndef BOUDBREAKSTATEMENT_H
#define BOUDBREAKSTATEMENT_H

#include "../../syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "../BoundStatement/BoundStatement.h"

class BoundBreakStatement : public BoundStatement {
private:
  BreakStatementSyntax *_syntax;

public:
  BoundBreakStatement(BreakStatementSyntax *syntax);

  ~BoundBreakStatement();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<BoundNode *> getChildren() override;

  BreakStatementSyntax *getBreakStatement() const;
};

#endif // BOUDBREAKSTATEMENT_H