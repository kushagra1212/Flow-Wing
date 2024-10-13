
#include "IfStatementBinder.h"

std::unique_ptr<BoundStatement>
IfStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                 StatementSyntax *statement) {
  IfStatementSyntax *ifStatement = static_cast<IfStatementSyntax *>(statement);

  std::unique_ptr<BoundIfStatement> boundIfStatement =
      std::make_unique<BoundIfStatement>(ifStatement->getSourceLocation());

  std::unique_ptr<BoundExpression> boundCondition = std::move(
      ExpressionBinderFactory::create(ifStatement->getConditionRef()->getKind())
          ->bindExpression(ctx, ifStatement->getConditionRef().get()));

  std::unique_ptr<BoundStatement> boundThenStatement = std::move(
      StatementBinderFactory::create(ifStatement->getStatementRef()->getKind())
          ->bindStatement(ctx, ifStatement->getStatementRef().get()));

  boundIfStatement->addCondition(std::move(boundCondition));
  boundIfStatement->addThenStatement(std::move(boundThenStatement));

  for (int i = 0; i < ifStatement->getOrIfStatementsRef().size(); i++) {
    std::unique_ptr<BoundOrIfStatement> boundOrIfStatement(
        static_cast<BoundOrIfStatement *>(
            StatementBinderFactory::create(
                ifStatement->getOrIfStatementsRef()[i]->getKind())
                ->bindStatement(ctx,
                                ifStatement->getOrIfStatementsRef()[i].get())
                .release()));

    boundIfStatement->addOrIfStatement(std::move(boundOrIfStatement));
  }

  std::unique_ptr<BoundStatement> boundElseStatement = nullptr;

  if (ifStatement->getElseClauseRef() != nullptr) {
    boundElseStatement = std::move(
        StatementBinderFactory::create(
            ifStatement->getElseClauseRef()->getStatementRef()->getKind())
            ->bindStatement(
                ctx, ifStatement->getElseClauseRef()->getStatementRef().get()));

    boundIfStatement->addElseStatement(std::move(boundElseStatement));
  }

  return std::move(boundIfStatement);
}
