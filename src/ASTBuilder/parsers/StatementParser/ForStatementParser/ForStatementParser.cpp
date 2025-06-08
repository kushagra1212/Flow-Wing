#include "ForStatementParser.h"
#include <memory>

std::unique_ptr<StatementSyntax>
ForStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> keyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ForKeyword));
  ctx->getCodeFormatterRef()->appendWithSpace();
  bool hadOpenParenthesis = false;
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);
    hadOpenParenthesis = true;
  }

  std::unique_ptr<StatementSyntax> statementSyntax = nullptr;

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::VarKeyword) {
    std::unique_ptr<VariableDeclarationParser> varDecParser =
        std::make_unique<VariableDeclarationParser>();
    // varDecParser->setIsForStatement(true);
    statementSyntax = std::move(varDecParser->parseStatement(ctx));
  } else {
    statementSyntax = std::move(
        std::make_unique<ExpressionStatementParser>()->parseStatement(ctx));
  }
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<SyntaxToken<std::any>> toKeyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ToKeyword));
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<ExpressionSyntax> upperBound =
      std::move(PrecedenceAwareExpressionParser::parse(ctx));
  std::unique_ptr<ExpressionSyntax> step = nullptr;
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken) {
    ctx->getCodeFormatterRef()->appendWithSpace();
    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->getCodeFormatterRef()->appendWithSpace();
    step = std::move(PrecedenceAwareExpressionParser::parse(ctx));
  }

  if (hadOpenParenthesis) {
    ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
  }
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> statement(
      static_cast<BlockStatementSyntax *>(
          std::make_unique<BlockStatementParser>()
              ->parseStatement(ctx)
              .release()));

  return std::make_unique<ForStatementSyntax>(
      std::move(statementSyntax), std::move(upperBound), std::move(statement),
      std::move(step));
}
