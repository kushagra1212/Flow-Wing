#include "GlobalStatementParser.h"
#include <memory>

std::unique_ptr<MemberSyntax>
GlobalStatementParser::parseStatement(ParserContext *ctx) {

  SyntaxKindUtils::SyntaxKind currentKind = ctx->getKind();

  if (currentKind == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    currentKind = ctx->peek(1)->getKind();
  }

  std::unique_ptr<StatementSyntax> statement =
      std::move(StatementParserFactory::createStatementParser(currentKind)
                    ->parseStatement(ctx));

  ctx->getCodeFormatterRef()->appendNewLine();
  return std::make_unique<GlobalStatementSyntax>(std::move(statement));
}
