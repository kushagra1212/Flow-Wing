#include "IndexExpressionBinder.h"
#include "../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"
#include <memory>

std::unique_ptr<BoundExpression>
IndexExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                      ExpressionSyntax *expression) {
  IndexExpressionSyntax *indexExpression =
      static_cast<IndexExpressionSyntax *>(expression);

  std::string variableName = std::any_cast<std::string>(
      indexExpression->getIndexIdentifierExpressionRef()->getValue());

  if (!ctx->getRootRef()->tryLookupVariable(variableName)) {

    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {variableName},
                   Utils::getSourceLocation(
                       indexExpression->getIndexIdentifierExpressionRef()
                           ->getTokenPtr()
                           .get()),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::VariableNotFound));

    return std::move(
        ExpressionBinderFactory::create(
            indexExpression->getIndexIdentifierExpressionRef()->getKind())
            ->bindExpression(
                ctx, indexExpression->getIndexIdentifierExpressionRef().get()));
  }

  BoundVariableDeclaration *variable =
      ctx->getRootRef()->tryGetVariable(variableName);

  if (variable->getTypeExpression().get()->getSyntaxType() !=
          SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE &&
      variable->getTypeExpression().get()->getSyntaxType() !=
          SyntaxKindUtils::SyntaxKind::StrKeyword) {

    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {variableName},
        Utils::getSourceLocation(
            indexExpression->getIndexIdentifierExpressionRef()
                ->getTokenPtr()
                .get()),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::IndexingNonArrayVariable));

    return std::move(
        ExpressionBinderFactory::create(
            indexExpression->getIndexIdentifierExpressionRef()->getKind())
            ->bindExpression(
                ctx, indexExpression->getIndexIdentifierExpressionRef().get()));
  }

  std::unique_ptr<BoundLiteralExpression<std::any>> boundIdentifierExpression(
      (BoundLiteralExpression<std::any> *)ExpressionBinderFactory::create(
          indexExpression->getIndexIdentifierExpressionRef()->getKind())
          ->bindExpression(
              ctx, indexExpression->getIndexIdentifierExpressionRef().get())
          .release());

  std::unique_ptr<BoundIndexExpression> boundIndexExp =
      std::make_unique<BoundIndexExpression>(
          indexExpression->getSourceLocation(),
          std::move(boundIdentifierExpression));

  for (const auto &indexExp : indexExpression->getIndexExpressionsRef()) {
    boundIndexExp->addBoundIndexExpression(
        std::move(ExpressionBinderFactory::create(indexExp->getKind())
                      ->bindExpression(ctx, indexExp.get())));
  }

  if (indexExpression->isObject()) {
    VariableExpressionSyntax *variableExpressionSyntax =
        static_cast<VariableExpressionSyntax *>(
            indexExpression->getVariableExpressionRef().get());

    std::unique_ptr<BoundVariableExpression> boundVariableExpression =
        std::make_unique<BoundVariableExpression>(
            indexExpression->getSourceLocation(), nullptr,
            variableExpressionSyntax->isConstant(),
            variable->getTypeExpression().get());

    for (const auto &dotExpression :
         variableExpressionSyntax->getDotExpressionList()) {
      if (dotExpression->getKind() ==
          SyntaxKindUtils::SyntaxKind::IndexExpression) {
        IndexExpressionSyntax *indexExpression =
            static_cast<IndexExpressionSyntax *>(dotExpression.get());
        std::unique_ptr<BoundLiteralExpression<std::any>>
            localBoundIdentifierExpression(
                (BoundLiteralExpression<std::any> *)
                    ExpressionBinderFactory::create(
                        indexExpression->getIndexIdentifierExpressionRef()
                            ->getKind())
                        ->bindExpression(
                            ctx,
                            indexExpression->getIndexIdentifierExpressionRef()
                                .get())
                        .release());

        std::unique_ptr<BoundIndexExpression> localBoundIndexExp =
            std::make_unique<BoundIndexExpression>(
                indexExpression->getSourceLocation(),
                std::move(localBoundIdentifierExpression));

        for (const auto &indexExp : indexExpression->getIndexExpressionsRef()) {
          localBoundIndexExp->addBoundIndexExpression(
              std::move(ExpressionBinderFactory::create(indexExp->getKind())
                            ->bindExpression(ctx, indexExp.get())));
        }
        boundVariableExpression->addDotExpression(
            std::move(localBoundIndexExp));
      } else {
        boundVariableExpression->addDotExpression(
            std::move(ExpressionBinderFactory::create(dotExpression->getKind())
                          ->bindExpression(ctx, dotExpression.get())));
      }
    }

    boundIndexExp->addVariableExpression(std::move(boundVariableExpression));
  }

  boundIndexExp->setIsSelf(indexExpression->getIsSelf());

  return std::move(boundIndexExp);
}