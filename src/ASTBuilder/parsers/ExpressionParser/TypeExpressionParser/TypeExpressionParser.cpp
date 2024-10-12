#include "TypeExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
TypeExpressionParser::parseExpression(ParserContext *ctx) {
  if (ctx->peek(1)->getKind() ==
          SyntaxKindUtils::SyntaxKind::OpenBracketToken ||
      (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
       ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken &&
       ctx->peek(2)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken &&
       ctx->peek(4)->getKind() ==
           SyntaxKindUtils::SyntaxKind::OpenBracketToken)) {
    return std::move(
        std::make_unique<ArrayTypeExpressionParser>()->parseExpression(ctx));
  }

  if (ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken &&
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

    return std::move(objectType);
  }

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken &&
      ctx->peek(1)->getKind() ==
          SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    return std::move(
        std::make_unique<FunctionTypeExpressionParser>()->parseExpression(ctx));
  }

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken) {
    return std::move(
        std::make_unique<ObjectTypeExpressionParser>()->parseExpression(ctx));
  }

  return std::make_unique<TypeExpressionSyntax>(
      std::make_unique<PrimitiveTypeExpressionParser>()->parseExpression(ctx));
}