#include "FillExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
FillExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<FillExpressionSyntax> fillExpression =
      std::make_unique<FillExpressionSyntax>();

  ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

  std::unique_ptr<ExpressionSyntax> sizeToFillExpression = nullptr;

  auto numToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::NumberToken));
  ctx->getCodeFormatterRef()->appendWithSpace();
  std::any sizeVAL = numToken->getValue();

  sizeToFillExpression = std::make_unique<LiteralExpressionSyntax<std::any>>(
      std::move(numToken), sizeVAL);

  ctx->match(SyntaxKindUtils::SyntaxKind::FillKeyword);
  ctx->getCodeFormatterRef()->appendWithSpace();
  std::unique_ptr<ExpressionSyntax> elementExpression =
      std::move(PrecedenceAwareExpressionParser::parse(ctx));

  ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);

  fillExpression->setSizeToFillExpression(std::move(sizeToFillExpression));
  fillExpression->setElementExpression(std::move(elementExpression));

  return std::move(fillExpression);
}