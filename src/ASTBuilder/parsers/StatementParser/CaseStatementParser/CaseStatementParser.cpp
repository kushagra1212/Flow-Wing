#include "CaseStatementParser.h"

std::unique_ptr<StatementSyntax>
CaseStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<CaseStatementSyntax> caseStatement =
      std::make_unique<CaseStatementSyntax>();

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::DefaultKeyword) {
    caseStatement->setDefaultToken(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::DefaultKeyword)));
  } else {
    caseStatement->setCaseToken(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CaseKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
    caseStatement->setCaseExpression(
        std::move(PrecedenceAwareExpressionParser::parse(ctx)));
  }
  ctx->getCodeFormatterRef()->appendWithSpace();
  caseStatement->setColonToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken)));
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> blockStatementSyntax(
      static_cast<BlockStatementSyntax *>(
          std::make_unique<BlockStatementParser>()
              ->parseStatement(ctx)
              .release()));

  caseStatement->setBlockStatement(std::move(blockStatementSyntax));
  ctx->getCodeFormatterRef()->appendNewLine();

  return std::move(caseStatement);
}
