
#include "CaseStatementBinder.h"

std::unique_ptr<BoundStatement>
CaseStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                   StatementSyntax *statement) {

  CaseStatementSyntax *caseStatement =
      static_cast<CaseStatementSyntax *>(statement);

  std::unique_ptr<BoundCaseStatement> boundCaseStatement =
      std::make_unique<BoundCaseStatement>(caseStatement->getSourceLocation());

  boundCaseStatement->setIsDefaultCase(caseStatement->isDefaultCase());

  if (!boundCaseStatement->getIsDefaultCase()) {
    boundCaseStatement->setCaseExpression(
        std::move(ExpressionBinderFactory::create(
                      caseStatement->getCaseExpressionRef()->getKind())
                      ->bindExpression(
                          ctx, caseStatement->getCaseExpressionRef().get())));
  }

  boundCaseStatement->setBodyStatement(std::move(
      StatementBinderFactory::create(
          caseStatement->getBlockStatementRef()->getKind())
          ->bindStatement(ctx, caseStatement->getBlockStatementRef().get())));

  return std::move(boundCaseStatement);
}