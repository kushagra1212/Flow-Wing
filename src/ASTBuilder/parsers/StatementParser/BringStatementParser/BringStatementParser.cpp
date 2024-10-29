#include "BringStatementParser.h"

#include "../../../ASTBuilder.h"

std::unique_ptr<StatementSyntax>
BringStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> bringKeyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::BringKeyword));
  ctx->getCodeFormatterRef()->appendWithSpace();
  std::unique_ptr<BringStatementSyntax> bringStatement =
      std::make_unique<BringStatementSyntax>();

  bringStatement->addBringKeyword(std::move(bringKeyword));

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBraceToken) {
    bringStatement->addOpenBraceToken(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken)));
    while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      std::unique_ptr<SyntaxToken<std::any>> identifier =
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
      std::string importExpName = identifier->getText();
      bringStatement->addExpression(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifier), importExpName));

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
        ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
        ctx->getCodeFormatterRef()->appendWithSpace();
      }

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
        ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
            "Unexpected Token <" + SyntaxKindUtils::to_string(ctx->getKind()) +
                ">, Expected <" +
                SyntaxKindUtils::to_string(
                    SyntaxKindUtils::SyntaxKind::CloseBraceToken) +
                ">",
            DiagnosticUtils::DiagnosticLevel::Error,
            DiagnosticUtils::DiagnosticType::Syntactic,
            Utils::getSourceLocation(ctx->getCurrent())));
        return std::move(bringStatement);
      }
    }
    ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);
    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  if (bringStatement->getIsChoosyImportPtr()) {
    ctx->match(SyntaxKindUtils::SyntaxKind::FromKeyword);
    ctx->getCodeFormatterRef()->appendWithSpace();
  }
  bool isModule = false;
  std::unique_ptr<SyntaxToken<std::any>> stringToken = nullptr;
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken) {
    stringToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
  } else if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::StringToken) {
    stringToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::StringToken));
  } else if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::StringToken) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        "Unexpected Token <" + SyntaxKindUtils::to_string(ctx->getKind()) +
            ">, Expected <" +
            SyntaxKindUtils::to_string(
                SyntaxKindUtils::SyntaxKind::StringToken) +
            ">",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Syntactic,
        Utils::getSourceLocation(ctx->getCurrent())));
    return std::move(bringStatement);
  }

  std::string relativeFilePath = "";

  if (stringToken->getValue().type() == typeid(std::string)) {
    relativeFilePath = std::any_cast<std::string>(stringToken->getValue());

    if (relativeFilePath.find(".fg") == std::string::npos) {

      isModule = true;
      const std::string currentDirPath =
          std::filesystem::path(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath())
              .parent_path()
              .string();

      bringStatement->setModuleName(relativeFilePath);
      std::string moduleFilePath =
          Utils::findFile(std::string(FLOWWING_MODULE_PATH),
                          relativeFilePath + "-module.fg")
              .string();

      if (moduleFilePath.empty()) {
        moduleFilePath =
            Utils::findFile(currentDirPath, relativeFilePath + "-module.fg")
                .string();
      }

      if (moduleFilePath.empty()) {
        ctx->getDiagnosticHandler()->addDiagnostic(
            Diagnostic("Module <" + relativeFilePath + "> not found",
                       DiagnosticUtils::DiagnosticLevel::Error,
                       DiagnosticUtils::DiagnosticType::Syntactic,
                       Utils::getSourceLocation(stringToken.get())));

        return std::move(bringStatement);
      }

      DEBUG_LOG("Module File Path: " + moduleFilePath);

      relativeFilePath =
          std::filesystem::relative(moduleFilePath, currentDirPath).string();
      stringToken->setValue((relativeFilePath));
    }
    // appendNewLine();
  }
  bringStatement->setIsModuleImport(isModule);

  bringStatement->addPathToken(std::move(stringToken));

  bringStatement->setRelativeFilePath(relativeFilePath);

  std::string absoluteFilePath =
      std::filesystem::path(ctx->getDiagnosticHandler()->getAbsoluteFilePath())
          .parent_path()
          .string() +
      "/" + relativeFilePath;

  std::unique_ptr<FlowWing::DiagnosticHandler> diagnosticHandler =
      std::make_unique<FlowWing::DiagnosticHandler>(absoluteFilePath);

  if (ctx->getDependencyFileCount(absoluteFilePath) == 1) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic("Found Circular Reference <" + absoluteFilePath + ">",
                   DiagnosticUtils::DiagnosticLevel::Warning,
                   DiagnosticUtils::DiagnosticType::Syntactic,
                   Utils::getSourceLocation(ctx->getCurrent())));

    SyntaxKindUtils::SyntaxKind currentKind = ctx->getKind();

    if (currentKind == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
      currentKind = ctx->peek(1)->getKind();
    }

    return std::move(StatementParserFactory::createStatementParser(currentKind)
                         ->parseStatement(ctx));
  }

  ctx->updateDependencyCount(absoluteFilePath, 1);

  bringStatement->setAbsoluteFilePath(absoluteFilePath);

  ctx->getDiagnosticHandler()->addParentDiagnostics(diagnosticHandler.get());
  bringStatement->setDiagnosticHandler(std::move(diagnosticHandler));

  std::unique_ptr<ASTBuilder> parser = std::make_unique<ASTBuilder>(
      Utils::readLines(absoluteFilePath),
      bringStatement->getDiagnosticHandlerPtr().get());

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::move(parser->createCompilationUnit());

  bringStatement->setCompilationUnit(std::move(compilationUnit));

  ctx->updateDependencyCount(absoluteFilePath, -1);

  return std::move(bringStatement);
}
