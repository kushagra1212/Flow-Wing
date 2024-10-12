#pragma once

#include "../../../../syntax/expression/FillExpressionSyntax/FillExpressionSyntax.h"
#include "../ExpressionParser.h"
#include "../PrecedenceAwareExpressionParser.h"

class FillExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};