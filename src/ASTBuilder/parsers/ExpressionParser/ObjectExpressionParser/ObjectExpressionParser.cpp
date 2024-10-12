#include "ObjectExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
ObjectExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<ObjectExpressionSyntax> objES =
      std::make_unique<ObjectExpressionSyntax>();
  objES->setOpenBraceToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken)));
  ctx->getCodeFormatterRef()->appendNewLine();

  ctx->getCodeFormatterRef()->appendIndentAmount(TAB_SPACE);

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());

    std::unique_ptr<SyntaxToken<std::any>> idenfierToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

    std::any val = idenfierToken->getValue();

    std::unique_ptr<LiteralExpressionSyntax<std::any>> idenfierExp =
        std::make_unique<LiteralExpressionSyntax<std::any>>(
            std::move(idenfierToken), val);

    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<ExpressionSyntax> expression =
        std::move(PrecedenceAwareExpressionParser::parse(ctx));

    objES->addAttribute(std::move(idenfierExp), std::move(expression));

    if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      ctx->getCodeFormatterRef()->appendNewLine();
    }
  }
  ctx->getCodeFormatterRef()->appendNewLine();

  ctx->getCodeFormatterRef()->setIndentAmount(
      ctx->getCodeFormatterRef()->getIndentAmount().substr(
          0, ctx->getCodeFormatterRef()->getIndentAmount().length() -
                 (sizeof(TAB_SPACE) - 1)));

  ctx->getCodeFormatterRef()->append(
      ctx->getCodeFormatterRef()->getIndentAmount());

  objES->setCloseBraceToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken)));

  return std::move(objES);
}