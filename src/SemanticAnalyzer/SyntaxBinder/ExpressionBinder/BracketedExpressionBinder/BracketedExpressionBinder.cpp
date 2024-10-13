#include "BracketedExpressionBinder.h"
#include <memory>

std::unique_ptr<BoundExpression>
BracketedExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                          ExpressionSyntax *expression) {
  BracketedExpressionSyntax *bracketedExpression =
      static_cast<BracketedExpressionSyntax *>(expression);

  SyntaxKindUtils::SyntaxKind kind =
      bracketedExpression->getExpressionRef()->getKind();

  std::unique_ptr<BoundBracketedExpression> boundBracketedExpression =
      std::make_unique<BoundBracketedExpression>(
          bracketedExpression->getSourceLocation());

  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::ContainerExpression:
  case SyntaxKindUtils::SyntaxKind::FillExpression: {
    boundBracketedExpression->setExpression(
        std::move(ExpressionBinderFactory::create(
                      bracketedExpression->getExpressionRef()->getKind())
                      ->bindExpression(
                          ctx, bracketedExpression->getExpressionRef().get())));
    break;
  }

  default: {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        "Invalid Bracketed Expression", DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        bracketedExpression->getSourceLocation()));
    break;
  }
  }

  return std::move(boundBracketedExpression);
}