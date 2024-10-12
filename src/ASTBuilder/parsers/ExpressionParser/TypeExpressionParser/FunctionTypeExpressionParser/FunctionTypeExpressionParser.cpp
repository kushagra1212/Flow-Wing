#include "FunctionTypeExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
FunctionTypeExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<FunctionTypeExpressionSyntax> funcTypeExpression =
      std::make_unique<FunctionTypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_FUNCTION_TYPE, 0,
              "NBU_FUNCTION_TYPE", "NBU_FUNCTION_TYPE"));

  funcTypeExpression->setOpenBracketToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken));

  funcTypeExpression->setOpenParenthesisToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken));

  ctx->getCodeFormatterRef()->appendWithSpace();
  size_t parameterCount = 0;
  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    if (parameterCount) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::AsKeyword) {
      funcTypeExpression->addAsParameterKeyword(
          parameterCount,
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::AsKeyword)));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    std::unique_ptr<TypeExpressionSyntax> typeExp(
        static_cast<TypeExpressionSyntax *>(
            std::make_unique<TypeExpressionParser>()
                ->parseExpression(ctx)
                .release()));

    funcTypeExpression->addParameterType(std::move(typeExp));

    parameterCount++;
  }

  ctx->getCodeFormatterRef()->appendWithSpace();

  funcTypeExpression->setCloseParenthesisToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken));

  ctx->getCodeFormatterRef()->appendWithSpace();
  ctx->match(SyntaxKindUtils::SyntaxKind::MinusToken);
  ctx->match(SyntaxKindUtils::SyntaxKind::GreaterToken);
  ctx->getCodeFormatterRef()->appendWithSpace();

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::AsKeyword) {
    funcTypeExpression->setAsKeyword(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::AsKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  do {
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
      funcTypeExpression->addSeparator(
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken)));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    funcTypeExpression->addReturnType(std::unique_ptr<TypeExpressionSyntax>(
        (static_cast<TypeExpressionSyntax *>(
            std::make_unique<TypeExpressionParser>()
                ->parseExpression(ctx)
                .release()))));

  } while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken);

  funcTypeExpression->setCloseBracketToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken));
  ctx->getCodeFormatterRef()->appendWithSpace();

  return std::move(funcTypeExpression);
}