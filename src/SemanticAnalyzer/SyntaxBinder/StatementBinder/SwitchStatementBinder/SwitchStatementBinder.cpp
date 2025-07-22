
#include "SwitchStatementBinder.h"
#include "../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"
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

  if (boundSwitchStatement->getHasNoDefaultCase()) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {},
        switchStatement->getSourceLocation(),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::NoDefaultCaseInSwitchStatement));

    return std::move(boundSwitchStatement);
  }

  if (boundSwitchStatement->getHasMoreThanOneDefaultCase()) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {},
                   switchStatement->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                       MoreThanOneDefaultCaseInSwitchStatement));
    return std::move(boundSwitchStatement);
  }

  if (!boundSwitchStatement->getHasAtLeastOneCaseStatement()) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {},
                   switchStatement->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                       NoCaseStatementInSwitchStatement));

    return std::move(boundSwitchStatement);
  }

  return std::move(boundSwitchStatement);
}