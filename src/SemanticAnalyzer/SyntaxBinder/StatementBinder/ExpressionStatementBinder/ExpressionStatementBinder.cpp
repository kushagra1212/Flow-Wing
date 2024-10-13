
#include "ExpressionStatementBinder.h"

std::unique_ptr<BoundStatement>
ExpressionStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                         StatementSyntax *statement) {

  ExpressionStatementSyntax *expressionStatement =
      static_cast<ExpressionStatementSyntax *>(statement);

  ExpressionSyntax *exps = expressionStatement->getExpressionPtr().get();

  std::unique_ptr<BoundExpression> boundExpression =
      std::move(ExpressionBinderFactory::create(exps->getKind())
                    ->bindExpression(ctx, exps));

  return std::make_unique<BoundExpressionStatement>(exps->getSourceLocation(),
                                                    std::move(boundExpression));
}