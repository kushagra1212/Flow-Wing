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
                    BoundLiteralExpression<std::any> *upperBound,

                    BoundStatement *statement);

  BoundVariableDeclaration *getVariableDeclaration() const;

  BoundStatement *getStatement() const;

  BoundLiteralExpression<std::any> *getUpperBound() const;

  BinderKindUtils::BoundNodeKind getKind() override;

private:
  BoundVariableDeclaration *variableDeclaration;

  BoundStatement *statement;

  BoundLiteralExpression<std::any> *upperBound;
};

#endif // BOUND_FOR_STATEMENT_H