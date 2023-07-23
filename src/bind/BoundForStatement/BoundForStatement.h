#ifndef BOUND_FOR_STATEMENT_H
#define BOUND_FOR_STATEMENT_H

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundForStatement : public BoundStatement {

public:
  BoundForStatement(BoundVariableDeclaration *variableDeclaration,
                    BoundExpression *upperBound,

                    BoundStatement *statement);

  BoundVariableDeclaration *getVariableDeclaration() const;

  BoundStatement *getStatement() const;

  BoundExpression *getUpperBound() const;

  BinderKindUtils::BoundNodeKind getKind() override;

private:
  BoundVariableDeclaration *variableDeclaration;

  BoundStatement *statement;

  BoundExpression *upperBound;
};

#endif // BOUND_FOR_STATEMENT_H