
#include "ContinueStatementBinder.h"
#include "../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"

std::unique_ptr<BoundStatement>
ContinueStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                       StatementSyntax *statement) {
  ContinueStatementSyntax *continueStatement =
      static_cast<ContinueStatementSyntax *>(statement);

  if (!ctx->getRootRef()->isContinuable()) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {},
        continueStatement->getSourceLocation(),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::ContinueStatementOutsideOfLoop));
  }
  return std::make_unique<BoundContinueStatement>(
      continueStatement->getSourceLocation());
}
