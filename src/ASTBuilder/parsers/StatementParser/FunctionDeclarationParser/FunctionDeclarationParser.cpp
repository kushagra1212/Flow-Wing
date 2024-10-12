#include "FunctionDeclarationParser.h"
#include <memory>

std::unique_ptr<MemberSyntax>
FunctionDeclarationParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<FunctionDeclarationSyntax> functionDeclaration =
      std::make_unique<FunctionDeclarationSyntax>();

  functionDeclaration->setIdentifierToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken)));

  functionDeclaration->setOpenParenthesisToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken)));

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    std::unique_ptr<VariableDeclarationSyntax> parameter = std::move(
        VariableParserUtils::parseSingleVariableDeclaration(ctx, true));

    functionDeclaration->addParameter(std::move(parameter));
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
      functionDeclaration->addSeparator(
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken)));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }
  }

  functionDeclaration->setFunctionType(std::make_unique<TypeExpressionSyntax>(
      std::make_unique<SyntaxToken<std::any>>(
          ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
          SyntaxKindUtils::SyntaxKind::StrKeyword, 0, "str", "str")));

  functionDeclaration->setCloseParenthesisToken(std::move(
      ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken)));
  ctx->getCodeFormatterRef()->appendWithSpace();

  ctx->match(SyntaxKindUtils::SyntaxKind::MinusToken);
  ctx->match(SyntaxKindUtils::SyntaxKind::GreaterToken);
  ctx->getCodeFormatterRef()->appendWithSpace();

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::AsKeyword) {
    functionDeclaration->setAsKeyword(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::AsKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  do {
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
      (ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    functionDeclaration->addReturnExpression(std::move(
        std::make_unique<TypeExpressionParser>()->parseExpression(ctx)));

  } while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken);

  ctx->getCodeFormatterRef()->appendWithSpace();

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::DeclKeyword)
    functionDeclaration->setDeclKeyword(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::DeclKeyword)));
  else {
    std::unique_ptr<BlockStatementSyntax> body(
        static_cast<BlockStatementSyntax *>(
            std::make_unique<BlockStatementParser>()
                ->parseStatement(ctx)
                .release()));

    functionDeclaration->setBody(std::move(body));
  }

  ctx->getCodeFormatterRef()->appendNewLine();
  ctx->getCodeFormatterRef()->appendNewLine();

  return std::move(functionDeclaration);
}
