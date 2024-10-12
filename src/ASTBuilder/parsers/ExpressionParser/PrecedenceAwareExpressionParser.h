#pragma once

#include "../../../syntax/expression/BinaryExpressionSyntax.h"
#include "../../../syntax/expression/ExpressionSyntax.h"
#include "../../../syntax/expression/UnaryExpressionSyntax.h"
#include "../ParserContext/ParserContext.h"
#include "PrimaryExpressionParserFactory.h"

class PrecedenceAwareExpressionParser {

public:
  static std::unique_ptr<ExpressionSyntax>
  parse(ParserContext *ctx, const int &parentPrecedence = 0);
};