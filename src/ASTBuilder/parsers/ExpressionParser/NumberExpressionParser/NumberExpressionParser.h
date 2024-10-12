#pragma once

#include "../../../../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../ExpressionParser.h"
#include "../LiteralExpressionParserUtils/LiteralExpressionParserUtils.h"
#include "../PrecedenceAwareExpressionParser.h"

class NumberExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};