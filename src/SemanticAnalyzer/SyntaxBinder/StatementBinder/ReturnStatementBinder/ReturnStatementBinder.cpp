
#include "ReturnStatementBinder.h"
#include "../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"

std::unique_ptr<BoundStatement>
ReturnStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                     StatementSyntax *statement) {

  ReturnStatementSyntax *returnStatement =
      static_cast<ReturnStatementSyntax *>(statement);

  std::unique_ptr<BoundReturnStatement> boundRetExpression =
      std::make_unique<BoundReturnStatement>(
          returnStatement->getSourceLocation());

  if (!ctx->getRootRef()->isInFunction()) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {},
                   returnStatement->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                       ReturnStatementOutsideOfFunction));
  } else {
    // TODO IMPLEMENT all Expression

    for (const auto &expr : returnStatement->getReturnExpressionListRef()) {
      boundRetExpression->addReturnExpression(
          std::move(ExpressionBinderFactory::create(expr->getKind())
                        ->bindExpression(ctx, expr.get())));
    }
  }

  return std::move(boundRetExpression);
}
