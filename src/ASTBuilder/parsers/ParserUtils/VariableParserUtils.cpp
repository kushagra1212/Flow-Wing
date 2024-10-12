#include "VariableParserUtils.h"
#include <memory>

void VariableParserUtils::handleVarDecParsePrefixKeywords(
    ParserContext *ctx, std ::unique_ptr<VariableDeclarationSyntax> &varDec,
    bool isFuncDec) {
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    varDec->setExposeKeyword(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  if (isFuncDec &&
      SyntaxKindUtils::SyntaxKind::InOutKeyword == ctx->getKind()) {
    varDec->setInoutKeyword(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::InOutKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  if (isFuncDec &&
      SyntaxKindUtils::SyntaxKind::ConstKeyword == ctx->getKind()) {
    varDec->setKeyword(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ConstKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }
  if (!isFuncDec) {
    varDec->setKeyword(std::move(
        ctx->match(SyntaxKindUtils::SyntaxKind::VarKeyword == ctx->getKind()
                       ? SyntaxKindUtils::SyntaxKind::VarKeyword
                       : SyntaxKindUtils::SyntaxKind::ConstKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }
}

void VariableParserUtils::handleVarDecParseInitializer(
    ParserContext *ctx, std::unique_ptr<VariableDeclarationSyntax> &varDec) {
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    ctx->getCodeFormatterRef()->appendWithSpace();
    std::unique_ptr<SyntaxToken<std::any>> equalsToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::EqualsToken));
    ctx->getCodeFormatterRef()->appendWithSpace();

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::NewKeyword) {
      varDec->setNewKeyword(
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::NewKeyword)));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    std::unique_ptr<ExpressionSyntax> initializer =
        std::move(PrecedenceAwareExpressionParser::parse(ctx));

    varDec->setInitializer(std::move(initializer));
  }
}

void VariableParserUtils::handleVarDecParseIdentifierAndType(
    ParserContext *ctx, std::unique_ptr<VariableDeclarationSyntax> &varDec) {
  std::unique_ptr<SyntaxToken<std::any>> identifier =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  varDec->setIdentifier(std::move(identifier));

  if (ctx->getCurrentModuleName() != "") {
    varDec->getIdentifierRef()->setValue(
        ctx->getCurrentModuleName() +
        FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
        std::any_cast<std::string>(varDec->getIdentifierRef()->getValue()));

    varDec->getIdentifierRef()->setText(
        std::any_cast<std::string>(varDec->getIdentifierRef()->getValue()));
  }

  std::unique_ptr<TypeExpressionSyntax> typeExpr =
      std::make_unique<TypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
              "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->getCodeFormatterRef()->appendWithSpace();
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::AsKeyword) {
      varDec->setAsKeyword(
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::AsKeyword)));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    typeExpr = std::move(std::unique_ptr<TypeExpressionSyntax>(
        static_cast<TypeExpressionSyntax *>(
            std::make_unique<TypeExpressionParser>()
                ->parseExpression(ctx)
                .release())));
  }
  varDec->setTypeExpr(std::move(typeExpr));
}

std::unique_ptr<VariableDeclarationSyntax>
VariableParserUtils::parseSingleVariableDeclaration(ParserContext *ctx,
                                                    bool isFuncDec) {
  std::unique_ptr<VariableDeclarationSyntax> varDec =
      std::make_unique<VariableDeclarationSyntax>();

  handleVarDecParsePrefixKeywords(ctx, varDec, isFuncDec);

  handleVarDecParseIdentifierAndType(ctx, varDec);

  handleVarDecParseInitializer(ctx, varDec);

  return std::move(varDec);
}