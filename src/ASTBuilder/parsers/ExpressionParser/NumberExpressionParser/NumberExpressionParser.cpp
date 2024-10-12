#include "NumberExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
NumberExpressionParser::parseExpression(ParserContext *ctx) {
  return LiteralExpressionParserUtils::parseExpression(
      ctx, SyntaxKindUtils::SyntaxKind::NumberToken);
}