
#include "ForStatementBinder.h"

std::unique_ptr<BoundStatement>
ForStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                  StatementSyntax *statement) {

  ForStatementSyntax *forStatement =
      static_cast<ForStatementSyntax *>(statement);

  ctx->insertScope();

  ctx->getRootRef()->makeBreakableAndContinuable();

  std::unique_ptr<BoundStatement> boundIntializer = std::move(
      StatementBinderFactory::create(
          forStatement->getInitializationRef()->getKind())
          ->bindStatement(ctx, forStatement->getInitializationRef().get()));

  std::unique_ptr<BoundExpression> boundUpperBound = std::move(
      ExpressionBinderFactory::create(
          forStatement->getUpperBoundRef()->getKind())
          ->bindExpression(ctx, forStatement->getUpperBoundRef().get()));

  std::unique_ptr<BoundExpression> boundStepExpression = nullptr;

  if (forStatement->getStepExpressionRef().get())
    boundStepExpression = std::move(
        ExpressionBinderFactory::create(
            forStatement->getStepExpressionRef()->getKind())
            ->bindExpression(ctx, forStatement->getStepExpressionRef().get()));

  std::unique_ptr<BoundStatement> boundBody = std::move(
      StatementBinderFactory::create(forStatement->getStatementRef()->getKind())
          ->bindStatement(ctx, forStatement->getStatementRef().get()));

  ctx->removeScope();

  return std::make_unique<BoundForStatement>(
      forStatement->getSourceLocation(), std::move(boundIntializer),
      std::move(boundUpperBound), std::move(boundStepExpression),
      std::move(boundBody));
}
