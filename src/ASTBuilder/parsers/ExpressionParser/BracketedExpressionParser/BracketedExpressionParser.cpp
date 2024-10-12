#include "BracketedExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
BracketedExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<BracketedExpressionSyntax> bracketedExpression =
      std::make_unique<BracketedExpressionSyntax>();

  if (ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::FillKeyword

      || ctx->peek(2)->getKind() == SyntaxKindUtils::SyntaxKind::FillKeyword) {

    bracketedExpression->setExpression(std::move(
        std::make_unique<FillExpressionParser>()->parseExpression(ctx)));

  } else {
    bracketedExpression->setExpression(std::move(
        std::make_unique<ContainerExpressionParser>()->parseExpression(ctx)));
  }

  return std::move(bracketedExpression);
}