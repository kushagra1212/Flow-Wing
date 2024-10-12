#include "IfStatementParser.h"
#include <memory>

std::unique_ptr<StatementSyntax>
IfStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<IfStatementSyntax> ifStatement =
      std::make_unique<IfStatementSyntax>();

  std::unique_ptr<SyntaxToken<std::any>> keyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IfKeyword));
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<ExpressionSyntax> condition =
      std::move(PrecedenceAwareExpressionParser::parse(ctx));
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> statement(
      static_cast<BlockStatementSyntax *>(
          std::make_unique<BlockStatementParser>()
              ->parseStatement(ctx)
              .release()));
  // appendNewLine();
  ifStatement->addIfKeyword(std::move(keyword));
  ifStatement->addCondition(std::move(condition));
  ifStatement->addStatement(std::move(statement));

  while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OrKeyword) {
    // _formattedSourceCode += INDENT;
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<SyntaxToken<std::any>> orKeyword =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OrKeyword));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<SyntaxToken<std::any>> ifKeyword =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IfKeyword));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<ExpressionSyntax> condition =
        std::move(PrecedenceAwareExpressionParser::parse(ctx));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<BlockStatementSyntax> statement(
        static_cast<BlockStatementSyntax *>(
            std::make_unique<BlockStatementParser>()
                ->parseStatement(ctx)
                .release()));
    // appendNewLine();

    ifStatement->addOrIfStatement(std::make_unique<OrIfStatementSyntax>(
        std::move(orKeyword), std::move(ifKeyword), std::move(condition),
        std::move(statement)));
  }
  std::unique_ptr<ElseClauseSyntax> elseClause = nullptr;

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ElseKeyword) {
    // _formattedSourceCode += INDENT;
    ctx->getCodeFormatterRef()->appendWithSpace();
    elseClause = std::unique_ptr<ElseClauseSyntax>(
        static_cast<ElseClauseSyntax *>(std::make_unique<ElseStatementParser>()
                                            ->parseStatement(ctx)
                                            .release()));
  }

  ifStatement->addElseClause(std::move(elseClause));

  return std::move(ifStatement);
}
