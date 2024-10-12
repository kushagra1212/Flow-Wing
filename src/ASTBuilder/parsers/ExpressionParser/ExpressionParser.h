#pragma once

#include "../../../syntax/expression/ExpressionSyntax.h"
#include "../ParserContext/ParserContext.h"

class ExpressionParser {
public:
  virtual ~ExpressionParser() = default;
  virtual std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) = 0;
};
