#include "ContainerExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
ContainerExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<ContainerExpressionSyntax> containerExpression =
      std::make_unique<ContainerExpressionSyntax>();

  ctx->setIsInsideContainerExpression(true);

  containerExpression->setOpenBracketToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken)));

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBracketToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    std::unique_ptr<ExpressionSyntax> expression = nullptr;

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
      expression = std::move(this->parseExpression(ctx));
    } else {
      expression = std::move(PrecedenceAwareExpressionParser::parse(ctx));
    }

    containerExpression->setElement(std::move(expression));

    if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBracketToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      ctx->getCodeFormatterRef()->appendWithSpace();
    }
  }

  containerExpression->setCloseBracketToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken)));

  ctx->setIsInsideContainerExpression(false);

  return std::move(containerExpression);
}