#include "ElseStatementParser.h"

std::unique_ptr<StatementSyntax>
ElseStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> elseKeyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ElseKeyword));
  ctx->getCodeFormatterRef()->appendWithSpace();
  std::unique_ptr<BlockStatementSyntax> elseStatement(
      static_cast<BlockStatementSyntax *>(
          std::make_unique<BlockStatementParser>()
              ->parseStatement(ctx)
              .release()));

  return std::make_unique<ElseClauseSyntax>(std::move(elseKeyword),
                                            std::move(elseStatement));
}
