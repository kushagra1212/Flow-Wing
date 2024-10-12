#include "BlockStatementParser.h"

std::unique_ptr<StatementSyntax>
BlockStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<BlockStatementSyntax> blockStatement =
      std::make_unique<BlockStatementSyntax>();

  std::unique_ptr<SyntaxToken<std::any>> openBraceToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken));
  ctx->getCodeFormatterRef()->appendNewLine();

  blockStatement->setOpenBraceToken(std::move(openBraceToken));

  std::vector<std::unique_ptr<StatementSyntax>> statements;
  ctx->getCodeFormatterRef()->appendIndentAmount(TAB_SPACE);

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());

    SyntaxKindUtils::SyntaxKind currentKind = ctx->getKind();

    if (currentKind == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
      currentKind = ctx->peek(1)->getKind();
    }

    blockStatement->addStatement(
        std::move(StatementParserFactory::createStatementParser(currentKind)
                      ->parseStatement(ctx)));

    ctx->getCodeFormatterRef()->appendNewLine();
  }
  ctx->getCodeFormatterRef()->setIndentAmount(
      ctx->getCodeFormatterRef()->getIndentAmount().substr(
          0, ctx->getCodeFormatterRef()->getIndentAmount().length() -
                 (sizeof(TAB_SPACE) - 1)));

  ctx->getCodeFormatterRef()->append(
      ctx->getCodeFormatterRef()->getIndentAmount());

  std::unique_ptr<SyntaxToken<std::any>> closeBraceToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken));

  blockStatement->setCloseBraceToken(std::move(closeBraceToken));

  return std::move(blockStatement);
}
