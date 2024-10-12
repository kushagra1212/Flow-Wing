#include "VariableExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
VariableExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> identifierToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  if (identifierToken->getValue().type() == typeid(std::string) &&
      std::any_cast<std::string>(identifierToken->getValue()) == "self") {
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::DotToken);

      auto expression = std::move(
          std::make_unique<IdentifierExpressionParser>()->parseExpression(ctx));

      if (auto *variExp =
              dynamic_cast<VariableExpressionSyntax *>(expression.get())) {
        variExp->setSelfKeyword(std::move(identifierToken));
      } else if (auto *indexExp =
                     dynamic_cast<IndexExpressionSyntax *>(expression.get())) {
        indexExp->addSelfKeyword(std::move(identifierToken));
      } else if (auto *assignExp = dynamic_cast<AssignmentExpressionSyntax *>(
                     expression.get())) {
        if (auto *memberExp = dynamic_cast<VariableExpressionSyntax *>(
                assignExp->getLeftPtr().get())) {
          memberExp->setSelfKeyword(std::move(identifierToken));
        } else if (auto *memberExp = dynamic_cast<IndexExpressionSyntax *>(
                       assignExp->getLeftPtr().get())) {
          memberExp->addSelfKeyword(std::move(identifierToken));
        }
      }

      return std::move(expression);
    } else {
      std::any value = identifierToken->getValue();

      std::unique_ptr<TypeExpressionSyntax> typeExpression =
          std::make_unique<TypeExpressionSyntax>(
              std::make_unique<SyntaxToken<std::any>>(
                  ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
                  SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
                  "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

      std::unique_ptr<VariableExpressionSyntax> variExp =
          std::make_unique<VariableExpressionSyntax>(
              std::make_unique<LiteralExpressionSyntax<std::any>>(
                  std::move(identifierToken), value),
              false, std::move(typeExpression));

      return std::move(variExp);
    }
  }

  std::any value = identifierToken->getValue();

  std::unique_ptr<TypeExpressionSyntax> typeExpression =
      std::make_unique<TypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
              "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

  std::unique_ptr<VariableExpressionSyntax> variExp =
      std::make_unique<VariableExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifierToken), value),
          false, std::move(typeExpression));

  while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::DotToken);

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
        ctx->peek(1)->getKind() ==
            SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

      std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken =
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

      std::any value = localIdentifierToken->getValue();
      std::unique_ptr<IndexExpressionSyntax> localIndexExpression =
          std::make_unique<IndexExpressionSyntax>(
              std::make_unique<LiteralExpressionSyntax<std::any>>(
                  std::move(localIdentifierToken), value));

      while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

        ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

        localIndexExpression->addIndexExpression(
            std::move(PrecedenceAwareExpressionParser::parse(ctx)));

        ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
      }

      variExp->addDotExpression(std::move(localIndexExpression));
    } else {

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
          ctx->peek(1)->getKind() ==
              SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {

        variExp->addDotExpression(std::move(
            std::make_unique<IdentifierExpressionParser>()->parseExpression(
                ctx)));
      } else {

        std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken =
            std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
        std::any value = localIdentifierToken->getValue();

        variExp->addDotExpression(
            std::make_unique<LiteralExpressionSyntax<std::any>>(
                std::move(localIdentifierToken), value));
      }
    }
  }

  return std::move(variExp);
}