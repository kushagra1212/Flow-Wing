
#include "ContinueStatementBinder.h"

std::unique_ptr<BoundStatement>
ContinueStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                       StatementSyntax *statement) {
  ContinueStatementSyntax *continueStatement =
      static_cast<ContinueStatementSyntax *>(statement);

  if (!ctx->getRootRef()->isContinuable()) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic("Continue Statement Outside Of Loop",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   Utils::getSourceLocation(
                       continueStatement->getContinueKeywordPtr().get())));
  }
  return std::make_unique<BoundContinueStatement>(
      continueStatement->getSourceLocation());
}
