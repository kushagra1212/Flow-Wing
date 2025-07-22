#include "ObjectTypeExpressionBinder.h"
#include "../../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"
#include <memory>

std::unique_ptr<BoundExpression>
ObjectTypeExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                           ExpressionSyntax *expression) {

  ObjectTypeExpressionSyntax *objectTypeExpressionSyntax =
      static_cast<ObjectTypeExpressionSyntax *>(expression);

  std::unique_ptr<BoundObjectTypeExpression> boundObjectTypeExpression =
      std::make_unique<BoundObjectTypeExpression>(
          objectTypeExpressionSyntax->getSourceLocation(),
          objectTypeExpressionSyntax->getTypeRef()->getKind());

  std::unique_ptr<BoundLiteralExpression<std::any>> oLitExpr(
      static_cast<BoundLiteralExpression<std::any> *>(
          ExpressionBinderFactory::create(
              objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                  ->getKind())
              ->bindExpression(
                  ctx, objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                           .get())
              .release()));

  boundObjectTypeExpression->setObjectTypeIdentifier(std::move(oLitExpr));

  std::string name = objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                         ->getTokenPtr()
                         ->getText();

  //! Verify if this is a class or object type
  boundObjectTypeExpression->setTypeName(name);

  //? name -> class Type or Object Type

  BoundCustomTypeStatement *bCT = ctx->getRootRef()->tryGetCustomType(name);
  BINDER_DEBUG_LOG("CURRENT_MODULE_NAME: " + name);

  if (!bCT && !ctx->getRootRef()->tryGetClass(name)) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {name},
                   objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                       ->getTokenPtr()
                       ->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::TypeOrClassNotFound));

    return std::move(boundObjectTypeExpression);
  }

  if (bCT) {
    std::unique_ptr<BoundLiteralExpression<std::any>> oLitExpr(
        static_cast<BoundLiteralExpression<std::any> *>(
            ExpressionBinderFactory::create(

                objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                    ->getKind())
                ->bindExpression(ctx, objectTypeExpressionSyntax
                                          ->getObjectTypeIdentifierRef()
                                          .get())
                .release()));

    boundObjectTypeExpression->setObjectTypeIdentifier(std::move(oLitExpr));

    boundObjectTypeExpression->setTypeName(bCT->getTypeNameAsString());
  }

  return std::move(boundObjectTypeExpression);
}