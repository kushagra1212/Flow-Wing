#include "ArrayTypeExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
ArrayTypeExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<ArrayTypeExpressionSyntax> arrayTypeExpression =
      std::make_unique<ArrayTypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE, 0, "NBU_ARRAY_TYPE",
              "NBU_ARRAY_TYPE"));

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
      ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken &&
      ctx->peek(2)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken) {
    std::unique_ptr<SyntaxToken<std::any>> iden =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);

    std::unique_ptr<ObjectTypeExpressionSyntax> objectType(
        static_cast<ObjectTypeExpressionSyntax *>(
            std::make_unique<ObjectTypeExpressionParser>()
                ->parseExpression(ctx)
                .release()));

    objectType->getObjectTypeIdentifierRef()->getTokenPtr()->setValue(
        std::any_cast<std::string>(iden->getValue()) +
        FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
        std::any_cast<std::string>(objectType->getObjectTypeIdentifierRef()
                                       ->getTokenPtr()
                                       ->getValue()));
    objectType->getObjectTypeIdentifierRef()->getTokenPtr()->setText(
        (iden->getText()) + FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
        (objectType->getObjectTypeIdentifierRef()->getTokenPtr()->getText()));
    arrayTypeExpression->setNonTrivialElementType(std::move(objectType));
  } else if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken) {
    arrayTypeExpression->setNonTrivialElementType(
        std::move(std::unique_ptr<ObjectTypeExpressionSyntax>(
            (static_cast<ObjectTypeExpressionSyntax *>(
                std::make_unique<ObjectTypeExpressionParser>()
                    ->parseExpression(ctx)
                    .release())))));

  } else {
    arrayTypeExpression->setElementType(std::move(
        std::make_unique<PrimitiveTypeExpressionParser>()->parseExpression(
            ctx)));
  }

  while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

    std::unique_ptr<SyntaxToken<std::any>> numToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::NumberToken));

    std::any value = numToken->getValue();

    arrayTypeExpression->addDimension(
        std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(numToken),
                                                            value));

    ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
  }

  return std::move(arrayTypeExpression);
}