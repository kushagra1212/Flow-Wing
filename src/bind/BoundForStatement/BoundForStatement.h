#ifndef BOUND_FOR_STATEMENT_H
#define BOUND_FOR_STATEMENT_H

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundForStatement : public BoundStatement {

private:
  std::unique_ptr<BoundStatement> _initialization;

  std::unique_ptr<BoundStatement> _statement;

  std::unique_ptr<BoundExpression> _upperBound;

public:
  BoundForStatement(std::string lineAndColumn,
                    std::unique_ptr<BoundStatement> initialization,
                    std::unique_ptr<BoundExpression> upperBound,

                    std::unique_ptr<BoundStatement> statement);

  std::unique_ptr<BoundStatement> getInitialization();

  std::unique_ptr<BoundStatement> getStatement();

  std::unique_ptr<BoundExpression> getUpperBound();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};

#endif // BOUND_FOR_STATEMENT_H