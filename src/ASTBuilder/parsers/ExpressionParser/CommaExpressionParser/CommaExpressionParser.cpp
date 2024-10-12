#include "CommaExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
CommaExpressionParser::parseExpression(ParserContext *ctx) {
  return LiteralExpressionParserUtils::parseExpression(
      ctx, SyntaxKindUtils::SyntaxKind::CommaToken);
}