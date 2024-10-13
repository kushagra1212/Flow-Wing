#include "TypeExpressionBinder.h"

std::unique_ptr<BoundExpression>
TypeExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                     ExpressionSyntax *expression) {

  TypeExpressionSyntax *typeExpressionSyntax =
      static_cast<TypeExpressionSyntax *>(expression);

  switch (typeExpressionSyntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::ArrayTypeExpression:
  case SyntaxKindUtils::SyntaxKind::PrimitiveTypeExpression:
  case SyntaxKindUtils::SyntaxKind::ObjectTypeExpression:
  case SyntaxKindUtils::SyntaxKind::FunctionTypeExpression: {
    return ExpressionBinderFactory::create(typeExpressionSyntax->getKind())
        ->bindExpression(ctx, typeExpressionSyntax);
  }
  default: {
    break;
  }
  }

  ctx->getDiagnosticHandler()->addDiagnostic(
      Diagnostic("Invalid Type Expression kind " +
                     std::to_string(typeExpressionSyntax->getKind()),
                 DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Semantic,
                 typeExpressionSyntax->getSourceLocation()));

  return nullptr;
}