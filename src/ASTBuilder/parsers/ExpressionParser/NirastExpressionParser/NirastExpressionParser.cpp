#include "NirastExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
NirastExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<LiteralExpressionSyntax<std::any>> litExpr(
      static_cast<LiteralExpressionSyntax<std::any> *>(
          LiteralExpressionParserUtils::parseExpression(
              ctx, SyntaxKindUtils::SyntaxKind::NirastKeyword)
              .release()));

  return std::make_unique<NirastExpressionSyntax>(std::move(litExpr));
}