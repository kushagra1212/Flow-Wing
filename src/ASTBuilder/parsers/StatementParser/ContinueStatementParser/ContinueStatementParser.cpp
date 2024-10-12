
#include "ContinueStatementParser.h"

std::unique_ptr<StatementSyntax>
ContinueStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> continueKeyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ContinueKeyword));
  return std::make_unique<ContinueStatementSyntax>(std::move(continueKeyword));
}
