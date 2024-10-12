#include "CharacterExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
CharacterExpressionParser::parseExpression(ParserContext *ctx) {
  return LiteralExpressionParserUtils::parseExpression(
      ctx, SyntaxKindUtils::SyntaxKind::CharacterToken);
}