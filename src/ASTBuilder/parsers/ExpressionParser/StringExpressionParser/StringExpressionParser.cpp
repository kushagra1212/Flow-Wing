#include "StringExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
StringExpressionParser::parseExpression(ParserContext *ctx) {
  return LiteralExpressionParserUtils::parseExpression(
      ctx, SyntaxKindUtils::SyntaxKind::StringToken);
}