#include "WhileStatementParser.h"

std::unique_ptr<StatementSyntax>
WhileStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> keyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::WhileKeyword));
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<ExpressionSyntax> condition =
      std::move(PrecedenceAwareExpressionParser::parse(ctx));

  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> statement(
      static_cast<BlockStatementSyntax *>(
          std::make_unique<BlockStatementParser>()
              ->parseStatement(ctx)
              .release()));

  return std::make_unique<WhileStatementSyntax>(
      std::move(keyword), std::move(condition), std::move(statement));
}
