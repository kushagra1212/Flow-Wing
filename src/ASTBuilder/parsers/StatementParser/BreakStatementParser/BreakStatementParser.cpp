#include "BreakStatementParser.h"

std::unique_ptr<StatementSyntax>
BreakStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> breakKeyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::BreakKeyword));
  return std::make_unique<BreakStatementSyntax>(std::move(breakKeyword));
}
