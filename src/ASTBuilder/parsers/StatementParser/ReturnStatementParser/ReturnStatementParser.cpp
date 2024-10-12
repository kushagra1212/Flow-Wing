#include "ReturnStatementParser.h"

std::unique_ptr<StatementSyntax>
ReturnStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> returnKeyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ReturnKeyword));
  ctx->setIsInsideReturnStatement(true);
  std::unique_ptr<ReturnStatementSyntax> returnStatement =
      std::make_unique<ReturnStatementSyntax>(std::move(returnKeyword));

  auto parseStatementLambda = [&]() {
    do {

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
        ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
        ctx->getCodeFormatterRef()->appendWithSpace();
      }

      std::unique_ptr<ExpressionSyntax> expression =
          std::move(PrecedenceAwareExpressionParser::parse(ctx));

      returnStatement->addReturnExpression(std::move(expression));

    } while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken);
  };

  ctx->getCodeFormatterRef()->appendWithSpace();
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);
    ctx->getCodeFormatterRef()->appendWithSpace();
    parseStatementLambda();
    ctx->getCodeFormatterRef()->appendWithSpace();
    ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);

  } else if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::ColonToken) {
    parseStatementLambda();
  } else {
    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
  }

  ctx->setIsInsideReturnStatement(false);
  return std::move(returnStatement);
}
