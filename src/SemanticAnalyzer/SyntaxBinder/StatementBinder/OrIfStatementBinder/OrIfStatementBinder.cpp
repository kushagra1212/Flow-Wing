
#include "OrIfStatementBinder.h"

std::unique_ptr<BoundStatement>
OrIfStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                   StatementSyntax *statement) {

  OrIfStatementSyntax *orIfStatement =
      static_cast<OrIfStatementSyntax *>(statement);

  std::unique_ptr<BoundExpression> boundCondition = std::move(
      ExpressionBinderFactory::create(
          orIfStatement->getConditionPtr()->getKind())
          ->bindExpression(ctx, orIfStatement->getConditionPtr().get()));

  std::unique_ptr<BoundStatement> boundThenStatement = std::move(
      StatementBinderFactory::create(
          orIfStatement->getStatementPtr()->getKind())
          ->bindStatement(ctx, orIfStatement->getStatementPtr().get()));

  return std::make_unique<BoundOrIfStatement>(
      orIfStatement->getSourceLocation(), std::move(boundCondition),
      std::move(boundThenStatement));
}
