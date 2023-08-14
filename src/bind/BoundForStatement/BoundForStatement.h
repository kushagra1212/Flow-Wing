#ifndef BOUND_FOR_STATEMENT_H
#define BOUND_FOR_STATEMENT_H

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundForStatement : public BoundStatement {

private:
  std::shared_ptr<BoundStatement> _initialization;

  std::shared_ptr<BoundStatement> _statement;

  std::shared_ptr<BoundExpression> _upperBound;

public:
  BoundForStatement(const std::string &lineAndColumn,
                    std::shared_ptr<BoundStatement> initialization,
                    std::shared_ptr<BoundExpression> upperBound,

                    std::shared_ptr<BoundStatement> statement);

  std::shared_ptr<BoundStatement> getInitialization() const;

  std::shared_ptr<BoundStatement> getStatement() const;

  std::shared_ptr<BoundExpression> getUpperBound() const;

  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // BOUND_FOR_STATEMENT_H