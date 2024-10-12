#include "DefaultPrimaryExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
DefaultPrimaryExpressionParser::parseExpression(ParserContext *ctx) {

  std::unique_ptr<SyntaxToken<std::any>> expressionToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ExpressionStatement));

  return std::make_unique<LiteralExpressionSyntax<std::any>>(
      std::move(expressionToken), nullptr);
}