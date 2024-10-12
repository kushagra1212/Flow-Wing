#include "MultipleVariableDeclarationParser.h"

std::unique_ptr<StatementSyntax>
MultipleVariableDeclarationParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<MultipleVariableDeclarationSyntax> mulVarDec =
      std::make_unique<MultipleVariableDeclarationSyntax>();

  mulVarDec->addVariableDeclaration(std::move(_initialVarDec));
  while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<VariableDeclarationSyntax> varDec =
        std::make_unique<VariableDeclarationSyntax>();
    VariableParserUtils::handleVarDecParseIdentifierAndType(ctx, varDec);
    mulVarDec->addVariableDeclaration(std::move(varDec));
  }

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    ctx->getCodeFormatterRef()->appendWithSpace();
    std::unique_ptr<SyntaxToken<std::any>> equalsToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::EqualsToken));
    ctx->getCodeFormatterRef()->appendWithSpace();
    uint8_t index = 0;

    do {

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken)
        ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::NewKeyword) {
        mulVarDec->getVariableDeclarationListRef()[index]->setNewKeyword(
            std::move(ctx->match(SyntaxKindUtils::SyntaxKind::NewKeyword)));
        ctx->getCodeFormatterRef()->appendWithSpace();
      }

      std::unique_ptr<ExpressionSyntax> initializer =
          std::move(PrecedenceAwareExpressionParser::parse(ctx));
      mulVarDec->getVariableDeclarationListRef()[index++]->setInitializer(
          std::move(initializer));
    } while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken);
  }

  return std::move(mulVarDec);
}
