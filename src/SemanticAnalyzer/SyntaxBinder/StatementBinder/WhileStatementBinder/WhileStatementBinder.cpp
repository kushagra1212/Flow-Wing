
#include "WhileStatementBinder.h"

std::unique_ptr<BoundStatement>
WhileStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                    StatementSyntax *statement) {
  WhileStatementSyntax *whileStatement =
      static_cast<WhileStatementSyntax *>(statement);

  ctx->insertScope();

  ctx->getRootRef()->makeBreakableAndContinuable();

  std::unique_ptr<BoundExpression> boundCondition = std::move(
      ExpressionBinderFactory::create(
          whileStatement->getConditionRef()->getKind())
          ->bindExpression(ctx, whileStatement->getConditionRef().get()));

  std::unique_ptr<BoundStatement> boundBody = std::move(
      StatementBinderFactory::create(whileStatement->getBodyRef()->getKind())
          ->bindStatement(ctx, whileStatement->getBodyRef().get()));

  ctx->removeScope();

  return std::make_unique<BoundWhileStatement>(
      whileStatement->getSourceLocation(), std::move(boundCondition),
      std::move(boundBody));
}
