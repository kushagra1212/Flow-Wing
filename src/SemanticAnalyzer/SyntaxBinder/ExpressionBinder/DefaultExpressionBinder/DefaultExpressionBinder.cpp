#include "DefaultExpressionBinder.h"

std::unique_ptr<BoundExpression>
DefaultExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                        ExpressionSyntax *expression) {

  ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
      "Unknown expression kind " + std::to_string(expression->getKind()),
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Syntactic,
      expression->getSourceLocation()));

  return nullptr;
}