#include "FalseExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
FalseExpressionParser::parseExpression(ParserContext *ctx) {
  return LiteralExpressionParserUtils::parseExpression(
      ctx, SyntaxKindUtils::SyntaxKind::FalseKeyword);
}