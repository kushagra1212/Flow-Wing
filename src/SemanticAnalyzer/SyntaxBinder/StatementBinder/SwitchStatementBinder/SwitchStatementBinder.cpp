
#include "SwitchStatementBinder.h"
#include <memory>

std::unique_ptr<BoundStatement>
SwitchStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                     StatementSyntax *statement) {

  SwitchStatementSyntax *switchStatement =
      static_cast<SwitchStatementSyntax *>(statement);

  std::unique_ptr<BoundSwitchStatement> boundSwitchStatement =
      std::make_unique<BoundSwitchStatement>(
          switchStatement->getSourceLocation());

  boundSwitchStatement->setSwitchExpression(
      std::move(ExpressionBinderFactory::create(
                    switchStatement->getSwitchExpressionRef()->getKind())
                    ->bindExpression(
                        ctx, switchStatement->getSwitchExpressionRef().get())));

  std::unique_ptr<CaseStatementBinder> caseStatementBinder =
      std::make_unique<CaseStatementBinder>();

  for (auto &caseStatement : switchStatement->getCaseStatementsRef()) {
    std::unique_ptr<BoundCaseStatement> boundCaseStatement(
        static_cast<BoundCaseStatement *>(
            caseStatementBinder->bindStatement(ctx, caseStatement.get())
                .release()));

    boundSwitchStatement->addCaseStatement(std::move(boundCaseStatement));
  }

  const auto LOG_ERROR = [&](const std::string &message) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(message, DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   switchStatement->getSourceLocation()));
  };

  if (boundSwitchStatement->getHasNoDefaultCase()) {
    LOG_ERROR("No default case found in switch statement");
    return std::move(boundSwitchStatement);
  }

  if (boundSwitchStatement->getHasMoreThanOneDefaultCase()) {
    LOG_ERROR("More than one default case found in switch statement");
    return std::move(boundSwitchStatement);
  }

  if (!boundSwitchStatement->getHasAtLeastOneCaseStatement()) {
    LOG_ERROR(
        "No case statement found in switch statement, add at least one case "
        "statement");

    return std::move(boundSwitchStatement);
  }

  return std::move(boundSwitchStatement);
}