#ifndef BOUND_FOR_STATEMENT_H
#define BOUND_FOR_STATEMENT_H

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundForStatement : public BoundStatement, public BoundSourceLocation {
 private:
  std::unique_ptr<BoundStatement> _initialization;

  std::unique_ptr<BoundStatement> _statement;

  std::unique_ptr<BoundExpression> _upperBound;

  std::unique_ptr<BoundExpression> _boundStepExpression;

 public:
  BoundForStatement(const DiagnosticUtils::SourceLocation &location,
                    std::unique_ptr<BoundStatement> initialization,
                    std::unique_ptr<BoundExpression> upperBound,
                    std::unique_ptr<BoundExpression> boundStepExpression,
                    std::unique_ptr<BoundStatement> statement);

  std::unique_ptr<BoundStatement> getInitialization();

  std::unique_ptr<BoundStatement> getStatement();

  std::unique_ptr<BoundExpression> getUpperBound();

  std::unique_ptr<BoundExpression> getStepExpression();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundStatement> &getInitializationPtr();

  std::unique_ptr<BoundStatement> &getStatementPtr();

  std::unique_ptr<BoundExpression> &getUpperBoundPtr();

  std::unique_ptr<BoundExpression> &getStepExpressionPtr();
};

#endif  // BOUND_FOR_STATEMENT_H