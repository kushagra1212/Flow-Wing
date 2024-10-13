
#include "ReturnStatementBinder.h"

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
        Diagnostic("Return Statement Outside Of Function",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   returnStatement->getSourceLocation()));
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
