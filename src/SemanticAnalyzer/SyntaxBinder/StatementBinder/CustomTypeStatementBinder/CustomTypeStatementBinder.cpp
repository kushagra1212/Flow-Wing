
#include "CustomTypeStatementBinder.h"

std::unique_ptr<BoundStatement>
CustomTypeStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                         StatementSyntax *statement) {

  CustomTypeStatementSyntax *customTypeStatement =
      static_cast<CustomTypeStatementSyntax *>(statement);

  std::unique_ptr<BoundCustomTypeStatement> boundCustomTypeStatement =
      std::make_unique<BoundCustomTypeStatement>(
          customTypeStatement->getSourceLocation(),
          customTypeStatement->isExposed());

  std::unique_ptr<BoundLiteralExpression<std::any>> boundLiteralExpression(
      static_cast<BoundLiteralExpression<std::any> *>(
          ExpressionBinderFactory::create(
              customTypeStatement->getTypeNameRef()->getKind())
              ->bindExpression(ctx, customTypeStatement->getTypeNameRef().get())
              .release()));

  boundCustomTypeStatement->setTypeName(std::move(boundLiteralExpression));

  std::unordered_map<std::string, int8_t> attributes;

  for (int i = 0; i < customTypeStatement->getKeyTypePairsRef().size(); i++) {
    const std::string &key = customTypeStatement->getKeyTypePairsRef()[i]
                                 ->getKey()
                                 ->getTokenPtr()
                                 ->getText();

    if (attributes.find(key) != attributes.end()) {
      ctx->getDiagnosticHandler()->addDiagnostic(
          Diagnostic("Duplicate Attribute key " + key + " in Custom Type" +
                         Utils::getActualTypeName(
                             boundCustomTypeStatement->getTypeNameAsString()),
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     customTypeStatement->getKeyTypePairsRef()[i]
                         ->getKey()
                         ->getSourceLocation()));
      return std::move(boundCustomTypeStatement);
    }
    attributes[key] = 1;

    std::unique_ptr<BoundLiteralExpression<std::any>> boundLiteralExpression(
        static_cast<BoundLiteralExpression<std::any> *>(
            ExpressionBinderFactory::create(
                customTypeStatement->getKeyTypePairsRef()[i]
                    ->getKey()
                    ->getKind())
                ->bindExpression(ctx,
                                 customTypeStatement->getKeyTypePairsRef()[i]
                                     ->getKey()
                                     .get())
                .release()));

    std::unique_ptr<BoundTypeExpression> boundTypeExpression(
        static_cast<BoundTypeExpression *>(
            ExpressionBinderFactory::create(
                customTypeStatement->getKeyTypePairsRef()[i]
                    ->getValue()
                    ->getKind())
                ->bindExpression(ctx,
                                 customTypeStatement->getKeyTypePairsRef()[i]
                                     ->getValue()
                                     .get())
                .release()));

    boundCustomTypeStatement->addKeyTypePair(std::move(boundLiteralExpression),
                                             std::move(boundTypeExpression));
  }

  if (ctx->getCurrentModuleName() != "" &&
      !ctx->getRootRef()->tryDeclareCustomTypeGlobal(
          boundCustomTypeStatement.get())) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic("Duplicate Custom Type " +
                       Utils::getActualTypeName(
                           boundCustomTypeStatement->getTypeNameAsString()),
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   customTypeStatement->getTypeNameRef()->getSourceLocation()));
  }
  if (ctx->getCurrentModuleName() == "" &&
      !ctx->getRootRef()->tryDeclareCustomType(
          boundCustomTypeStatement.get())) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic("Duplicate Custom Type " +
                       Utils::getActualTypeName(
                           boundCustomTypeStatement->getTypeNameAsString()),
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   customTypeStatement->getTypeNameRef()->getSourceLocation()));
  }

  return std::move(boundCustomTypeStatement);
}