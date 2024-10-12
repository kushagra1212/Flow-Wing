#include "ModuleStatementParser.h"
#include <memory>

std::unique_ptr<StatementSyntax>
ModuleStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<ModuleStatementSyntax> moduleStatement =
      std::make_unique<ModuleStatementSyntax>();

  moduleStatement->addModuleKeyword(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ModuleKeyword)));

  ctx->getCodeFormatterRef()->appendWithSpace();

  moduleStatement->addOpenBracketToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken)));

  std::unique_ptr<LiteralExpressionSyntax<std::any>> modNameLitExp(
      static_cast<LiteralExpressionSyntax<std::any> *>(
          LiteralExpressionParserUtils::parseExpression(
              ctx, SyntaxKindUtils::SyntaxKind::IdentifierToken)
              .release()));

  moduleStatement->addModuleName(std::move(modNameLitExp));

  moduleStatement->addCloseBracketToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken)));

  ctx->getCodeFormatterRef()->appendNewLine();

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());
    SyntaxKindUtils::SyntaxKind kind = ctx->getKind();

    switch (kind) {
    case SyntaxKindUtils::SyntaxKind::VarKeyword:
    case SyntaxKindUtils::SyntaxKind::ConstKeyword: {

      ctx->setCurrentModuleName(
          moduleStatement->getModuleNameRef()->getTokenPtr()->getText());

      moduleStatement->addStatement(
          std::move(VariableParserUtils::parseSingleVariableDeclaration(ctx)));

      ctx->setCurrentModuleName("");
      break;
    }
    case SyntaxKindUtils::SyntaxKind::TypeKeyword: {

      ctx->setCurrentModuleName(
          moduleStatement->getModuleNameRef()->getTokenPtr()->getText());

      moduleStatement->addStatement(std::move(
          std::make_unique<CustomTypeStatementParser>()->parseStatement(ctx)));

      ctx->setCurrentModuleName("");
      break;
    }

    case SyntaxKindUtils::SyntaxKind::ClassKeyword: {

      ctx->setCurrentModuleName(
          moduleStatement->getModuleNameRef()->getTokenPtr()->getText());

      moduleStatement->addStatement(std::move(
          std::make_unique<ClassStatementParser>()->parseStatement(ctx)));

      ctx->setCurrentModuleName("");
      break;
    }
    case SyntaxKindUtils::SyntaxKind::FunctionKeyword: {

      std::unique_ptr<SyntaxToken<std::any>> functionKeyword = nullptr;

      functionKeyword =
          (std::move(ctx->match(SyntaxKindUtils::SyntaxKind::FunctionKeyword)));
      ctx->getCodeFormatterRef()->appendWithSpace();

      std::unique_ptr<FunctionDeclarationSyntax> functionDeclaration(
          static_cast<FunctionDeclarationSyntax *>(
              std::make_unique<FunctionDeclarationParser>()
                  ->parseStatement(ctx)
                  .release()));

      functionDeclaration->setFunctionKeyword(std::move(functionKeyword));
      functionDeclaration->setIsMemberFunction(false);

      moduleStatement->addStatement(std::move(functionDeclaration));
      break;
    }
    case SyntaxKindUtils::SyntaxKind::IdentifierToken: {
      moduleStatement->addStatement(std::move(
          std::make_unique<CallExpressionParser>()->parseExpression(ctx)));
      break;
    }
    default: {

      ctx->match(SyntaxKindUtils::SyntaxKind::EndOfFileToken);
      break;
    }
    }
    ctx->getCodeFormatterRef()->appendNewLine();
  }

  return std::move(moduleStatement);
}
