#pragma once

#include "../../../../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../PrecedenceAwareExpressionParser.h"

class LiteralExpressionParserUtils {
public:
  static std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx, const SyntaxKindUtils::SyntaxKind &kind);
};