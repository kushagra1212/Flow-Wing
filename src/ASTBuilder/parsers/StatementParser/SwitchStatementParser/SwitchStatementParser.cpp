

#include "SwitchStatementParser.h"
#include <memory>

std::unique_ptr<StatementSyntax>
SwitchStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SwitchStatementSyntax> switchStatement =
      std::make_unique<SwitchStatementSyntax>();
  switchStatement->setSwitchToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::SwitchKeyword)));

  ctx->getCodeFormatterRef()->appendWithSpace();

  switchStatement->setSwitchExpression(
      std::move(PrecedenceAwareExpressionParser::parse(ctx)));

  ctx->getCodeFormatterRef()->appendWithSpace();

  switchStatement->setOpenCurlyToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken)));

  ctx->getCodeFormatterRef()->appendNewLine();

  ctx->getCodeFormatterRef()->appendIndentAmount(TAB_SPACE);

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());
    std::unique_ptr<CaseStatementSyntax> caseStatement(
        static_cast<CaseStatementSyntax *>(
            std::make_unique<CaseStatementParser>()
                ->parseStatement(ctx)
                .release()));

    switchStatement->addCaseStatement(std::move(caseStatement));
  }

  ctx->getCodeFormatterRef()->setIndentAmount(
      ctx->getCodeFormatterRef()->getIndentAmount().substr(
          0, ctx->getCodeFormatterRef()->getIndentAmount().length() -
                 (sizeof(TAB_SPACE) - 1)));
  switchStatement->setCloseCurlyToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken)));

  ctx->getCodeFormatterRef()->appendNewLine();

  return std::move(switchStatement);
}
