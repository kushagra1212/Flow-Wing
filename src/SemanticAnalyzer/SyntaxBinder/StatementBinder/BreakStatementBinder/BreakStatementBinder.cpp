
#include "BreakStatementBinder.h"
#include "../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"

std::unique_ptr<BoundStatement>
BreakStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                    StatementSyntax *statement) {
  BreakStatementSyntax *breakStatement =
      static_cast<BreakStatementSyntax *>(statement);

  if (!ctx->getRootRef()->isBreakable()) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {},
        Utils::getSourceLocation(breakStatement->getBreakKeywordPtr().get()),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::InvalidBreakStatementUsage));
  }
  return std::make_unique<BoundBreakStatement>(
      breakStatement->getSourceLocation());
}
