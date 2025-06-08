#pragma once

#include "../../../syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "../ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "../ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "../ParserContext/ParserContext.h"
class VariableParserUtils {
public:
  static void handleVarDecParsePrefixKeywords(
      ParserContext *ctx, std::unique_ptr<VariableDeclarationSyntax> &varDec,
      bool isFuncDec);

  static void handleVarDecParseIdentifierAndType(
      ParserContext *ctx, std::unique_ptr<VariableDeclarationSyntax> &varDec,
      bool isForStatement = false);

  static void handleVarDecParseInitializer(
      ParserContext *ctx, std::unique_ptr<VariableDeclarationSyntax> &varDec);

  static std::unique_ptr<VariableDeclarationSyntax>
  parseSingleVariableDeclaration(ParserContext *ctx, bool isFuncDec = false);
};
