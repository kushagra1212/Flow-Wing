
#include "BreakStatementBinder.h"

std::unique_ptr<BoundStatement>
BreakStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                    StatementSyntax *statement) {
  BreakStatementSyntax *breakStatement =
      static_cast<BreakStatementSyntax *>(statement);

  if (!ctx->getRootRef()->isBreakable()) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        "Break Statement not within Loop or Switch",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(breakStatement->getBreakKeywordPtr().get())));
  }
  return std::make_unique<BoundBreakStatement>(
      breakStatement->getSourceLocation());
}
