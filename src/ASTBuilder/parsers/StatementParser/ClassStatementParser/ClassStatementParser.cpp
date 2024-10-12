#include "ClassStatementParser.h"
#include <memory>

std::unique_ptr<StatementSyntax>
ClassStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<ClassStatementSyntax> classSyn =
      std::make_unique<ClassStatementSyntax>();

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    classSyn->setExposeKeyword(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  classSyn->setClassKeyword(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ClassKeyword)));
  ctx->getCodeFormatterRef()->appendWithSpace();

  classSyn->setClassNameIdentifier(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken)));
  ctx->getCodeFormatterRef()->appendWithSpace();

  if (ctx->getCurrentModuleName() != "") {
    classSyn->getClassNameIdentifierRef()->setValue(
        ctx->getCurrentModuleName() +
        FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
        std::any_cast<std::string>(
            classSyn->getClassNameIdentifierRef()->getValue()));

    classSyn->getClassNameIdentifierRef()->setText(std::any_cast<std::string>(
        classSyn->getClassNameIdentifierRef()->getValue()));
  }
  ctx->setCurrentModuleName("");

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ExtendsKeyword) {
    classSyn->setExtendsKeyword(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ExtendsKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
    classSyn->setParentClassNameIdentifier(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken)));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  classSyn->setClassOpenBraceToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken)));

  ctx->getCodeFormatterRef()->appendIndentAmount(TAB_SPACE);
  ctx->getCodeFormatterRef()->appendNewLine();
  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());
    SyntaxKindUtils::SyntaxKind kind = ctx->getKind();

    switch (kind) {
    case SyntaxKindUtils::SyntaxKind::VarKeyword:
    case SyntaxKindUtils::SyntaxKind::ConstKeyword: {
      classSyn->addClassDataMember(
          std::move(VariableParserUtils::parseSingleVariableDeclaration(ctx)));

      break;
    }
    case SyntaxKindUtils::SyntaxKind::TypeKeyword: {
      classSyn->addCustomTypeStatement(
          std::move(std::unique_ptr<CustomTypeStatementSyntax>(
              static_cast<CustomTypeStatementSyntax *>(
                  std::make_unique<CustomTypeStatementParser>()
                      ->parseStatement(ctx)
                      .release()))));

      break;
    }

    default: {

      auto functionDeclaration =
          std::move(std::unique_ptr<FunctionDeclarationSyntax>(
              static_cast<FunctionDeclarationSyntax *>(
                  std::make_unique<FunctionDeclarationParser>()
                      ->parseStatement(ctx)
                      .release())));

      functionDeclaration->setIsMemberFunction(true);

      classSyn->addClassMemberFunction(std::move(functionDeclaration));
    }

    break;
    }
    ctx->getCodeFormatterRef()->appendNewLine();
  }
  ctx->getCodeFormatterRef()->setIndentAmount(
      ctx->getCodeFormatterRef()->getIndentAmount().substr(
          0, ctx->getCodeFormatterRef()->getIndentAmount().length() -
                 (sizeof(TAB_SPACE) - 1)));

  ctx->getCodeFormatterRef()->append(
      ctx->getCodeFormatterRef()->getIndentAmount());

  classSyn->setClassCloseBraceToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken)));

  return std::move(classSyn);
}
