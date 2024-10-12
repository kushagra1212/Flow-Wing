#include "LiteralExpressionParserUtils.h"

std::unique_ptr<ExpressionSyntax> LiteralExpressionParserUtils::parseExpression(
    ParserContext *ctx, const SyntaxKindUtils::SyntaxKind &kind) {
  std::unique_ptr<SyntaxToken<std::any>> syntaxToken =
      std::move(ctx->match(kind));

  std::any value = syntaxToken->getValue();

  return std::make_unique<LiteralExpressionSyntax<std::any>>(
      std::move(syntaxToken), value);
}
