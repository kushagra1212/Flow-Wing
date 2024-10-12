#include "TrueExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
TrueExpressionParser::parseExpression(ParserContext *ctx) {
  return LiteralExpressionParserUtils::parseExpression(
      ctx, SyntaxKindUtils::SyntaxKind::TrueKeyword);
}