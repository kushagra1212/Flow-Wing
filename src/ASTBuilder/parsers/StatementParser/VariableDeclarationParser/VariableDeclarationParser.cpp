#include "VariableDeclarationParser.h"

std::unique_ptr<StatementSyntax>
VariableDeclarationParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<VariableDeclarationSyntax> varDec =
      std::make_unique<VariableDeclarationSyntax>();

  VariableParserUtils::handleVarDecParsePrefixKeywords(ctx, varDec, false);

  VariableParserUtils::handleVarDecParseIdentifierAndType(ctx, varDec);

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {

    auto mulVarDec = std::make_unique<MultipleVariableDeclarationParser>();
    mulVarDec->setInitialVarDec(std::move(varDec));

    return std::move(mulVarDec->parseStatement(ctx));
  }

  VariableParserUtils::handleVarDecParseInitializer(ctx, varDec);

  return std::move(varDec);
}
