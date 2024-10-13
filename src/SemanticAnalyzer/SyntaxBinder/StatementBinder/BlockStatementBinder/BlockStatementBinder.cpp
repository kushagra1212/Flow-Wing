
#include "BlockStatementBinder.h"

std::unique_ptr<BoundStatement>
BlockStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                    StatementSyntax *statement) {

  BlockStatementSyntax *blockStatement =
      static_cast<BlockStatementSyntax *>(statement);

  ctx->insertScope();

  std::unique_ptr<BoundBlockStatement> boundBlockStatement =
      std::make_unique<BoundBlockStatement>(blockStatement->getSourceLocation(),
                                            false);

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    std::unique_ptr<BoundStatement> statement = std::move(
        StatementBinderFactory::create(
            blockStatement->getStatements()[i]->getKind())
            ->bindStatement(ctx, blockStatement->getStatements()[i].get()));

    boundBlockStatement->addStatement(std::move(statement));
  }

  ctx->removeScope();

  return std::move(boundBlockStatement);
}