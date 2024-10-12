#include "ParenthesizedExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
ParenthesizedExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> left =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken));

  std::unique_ptr<ExpressionSyntax> expression =
      std::move(PrecedenceAwareExpressionParser::parse(ctx));

  std::unique_ptr<SyntaxToken<std::any>> right =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken));

  return std::make_unique<ParenthesizedExpressionSyntax>(
      std::move(left), std::move(expression), std::move(right));
}