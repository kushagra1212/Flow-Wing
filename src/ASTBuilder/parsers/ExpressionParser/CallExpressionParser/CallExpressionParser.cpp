#include "CallExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
CallExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> newKeywordToken = nullptr;

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::NewKeyword) {
    newKeywordToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::NewKeyword));

    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  std::unique_ptr<SyntaxToken<std::any>> identifierToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  std::any val = identifierToken->getValue();

  if (ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    std::unique_ptr<ExpressionSyntax> expectedCallExpr = std::move(
        std::make_unique<IdentifierExpressionParser>()->parseExpression(ctx));

    const std::string PREFIX = std::any_cast<std::string>(val) +
                               FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX;

    if (expectedCallExpr->getKind() ==
        SyntaxKindUtils::SyntaxKind::CallExpression) {

      CallExpressionSyntax *callExp =
          static_cast<CallExpressionSyntax *>(expectedCallExpr.get());

      callExp->getIdentifierPtr()->setValue(
          PREFIX + std::any_cast<std::string>(
                       (callExp->getIdentifierPtr()->getValue())));

      callExp->getIdentifierPtr()->setText(
          std::any_cast<std::string>(callExp->getIdentifierPtr()->getValue()));
    }

    return std::move(expectedCallExpr);
  }

  std::unique_ptr<CallExpressionSyntax> callExpression =
      std::make_unique<CallExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifierToken), val));

  if (newKeywordToken) {
    callExpression->setNewKeyword(std::move(newKeywordToken));
  }

  std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken));

  callExpression->setOpenParenthesisToken(std::move(openParenthesisToken));

  ctx->setIsInsideCallExpression(true);

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    std::unique_ptr<ExpressionSyntax> expression =
        std::move(PrecedenceAwareExpressionParser::parse(ctx));

    callExpression->addArgument(std::move(expression));
    if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseParenthesisToken) {
      callExpression->addSeparator(
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken)));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }
  }

  ctx->setIsInsideCallExpression(false);
  std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken));

  callExpression->setCloseParenthesisToken(std::move(closeParenthesisToken));

  return std::move(callExpression);
}