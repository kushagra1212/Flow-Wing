#include "TernaryExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
TernaryExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<TernaryExpressionSyntax> ternaryExpression =
      std::make_unique<TernaryExpressionSyntax>();

  ctx->getCodeFormatterRef()->appendWithSpace();

  ternaryExpression->addQuestionToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::QuestionToken)));

  ctx->getCodeFormatterRef()->appendWithSpace();

  ternaryExpression->addTrueExpression(
      std::move(PrecedenceAwareExpressionParser::parse(ctx)));

  ctx->getCodeFormatterRef()->appendWithSpace();

  ternaryExpression->addColonToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken)));

  ctx->getCodeFormatterRef()->appendWithSpace();

  ternaryExpression->addFalseExpression(
      std::move(PrecedenceAwareExpressionParser::parse(ctx)));

  return std::move(ternaryExpression);
}