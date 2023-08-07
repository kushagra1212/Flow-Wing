#ifndef BOUNDCONTINUESTATEMENT_H
#define BOUNDCONTINUESTATEMENT_H

#include "../../syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "../BoundStatement/BoundStatement.h"

class BoundContinueStatement : public BoundStatement {
private:
  ContinueStatementSyntax *_syntax;

public:
  BoundContinueStatement(ContinueStatementSyntax *syntax);

  ~BoundContinueStatement();

public:
  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<BoundNode *> getChildren() override;

  ContinueStatementSyntax *getContinueStatement() const;
};

#endif // BOUNDCONTINUESTATEMENT_H