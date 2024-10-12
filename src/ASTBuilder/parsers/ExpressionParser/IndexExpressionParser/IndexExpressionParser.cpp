#include "IndexExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
IndexExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> identifierToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  ctx->setIsInsideIndexExpression(true);

  std::any value = identifierToken->getValue();
  std::unique_ptr<IndexExpressionSyntax> indexExpression =
      std::make_unique<IndexExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifierToken), value));

  while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

    indexExpression->addIndexExpression(
        std::move(PrecedenceAwareExpressionParser::parse(ctx)));

    ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
  }

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
    std::unique_ptr<TypeExpressionSyntax> typeExpression =
        std::make_unique<TypeExpressionSyntax>(
            std::make_unique<SyntaxToken<std::any>>(
                ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
                SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
                "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

    std::unique_ptr<VariableExpressionSyntax> variExp =
        std::make_unique<VariableExpressionSyntax>(
            std::make_unique<LiteralExpressionSyntax<std::any>>(nullptr, value),
            false, std::move(typeExpression));

    while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::DotToken);

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
          ctx->peek(1)->getKind() ==
              SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

        std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken =
            std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

        std::any value = localIdentifierToken->getValue();
        std::unique_ptr<IndexExpressionSyntax> localIndexExpression =
            std::make_unique<IndexExpressionSyntax>(
                std::make_unique<LiteralExpressionSyntax<std::any>>(
                    std::move(localIdentifierToken), value));

        while (ctx->getKind() ==
               SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

          ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

          localIndexExpression->addIndexExpression(
              std::move(PrecedenceAwareExpressionParser::parse(ctx)));

          ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
        }

        variExp->addDotExpression(std::move(localIndexExpression));
      } else {
        std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken =
            std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
        std::any value = localIdentifierToken->getValue();

        variExp->addDotExpression(
            std::make_unique<LiteralExpressionSyntax<std::any>>(
                std::move(localIdentifierToken), value));
      }
    }
    indexExpression->addVariableExpression(std::move(variExp));
  }

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    ctx->getCodeFormatterRef()->appendWithSpace();
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::EqualsToken));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<ExpressionSyntax> right =
        std::move(PrecedenceAwareExpressionParser::parse(ctx));

    ctx->setIsInsideIndexExpression(false);
    return std::make_unique<AssignmentExpressionSyntax>(
        std::move(indexExpression), operatorToken->getKind(), std::move(right));
  }

  ctx->setIsInsideIndexExpression(false);

  return std::move(indexExpression);
}