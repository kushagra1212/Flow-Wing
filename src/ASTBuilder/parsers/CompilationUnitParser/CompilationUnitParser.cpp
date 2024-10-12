#include "CompilationUnitParser.h"
#include <memory>

std::unique_ptr<MemberSyntax>
CompilationUnitParser::parseMember(ParserContext *ctx) {
  SyntaxKindUtils::SyntaxKind currentKind = ctx->getKind();

  if (currentKind == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    currentKind = ctx->peek(1)->getKind();
  }

  if (currentKind == SyntaxKindUtils::SyntaxKind::FunctionKeyword) {
    ctx->getCodeFormatterRef()->appendNewLine();

    std::unique_ptr<SyntaxToken<std::any>> exposedKeyword = nullptr,
                                           functionKeyword = nullptr;
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
      exposedKeyword =
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword));

      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    functionKeyword =
        (std::move(ctx->match(SyntaxKindUtils::SyntaxKind::FunctionKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<FunctionDeclarationSyntax> functionDeclaration(
        static_cast<FunctionDeclarationSyntax *>(
            std::make_unique<FunctionDeclarationParser>()
                ->parseStatement(ctx)
                .release()));

    functionDeclaration->setExposedKeyword(std::move(exposedKeyword));
    functionDeclaration->setFunctionKeyword(std::move(functionKeyword));
    functionDeclaration->setIsMemberFunction(false);

    return std::move(functionDeclaration);
  }

  return std::make_unique<GlobalStatementParser>()->parseStatement(ctx);
}

std::unique_ptr<CompilationUnitSyntax>
CompilationUnitParser::parseCompilationUnit(ParserContext *ctx) {
  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::make_unique<CompilationUnitSyntax>();

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    compilationUnit->addMember(std::move(parseMember(ctx)));
  }

  std::unique_ptr<SyntaxToken<std::any>> endOfFileToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::EndOfFileToken));

  compilationUnit->setEndOfFileToken(std::move(endOfFileToken));

  return std::move(compilationUnit);
}