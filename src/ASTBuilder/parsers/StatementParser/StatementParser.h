#pragma once

#include "../../../syntax/statements/StatementSyntax.h"
#include "../ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "../ParserContext/ParserContext.h"

class StatementParser {
public:
  virtual ~StatementParser() = default;
  virtual std::unique_ptr<StatementSyntax>
  parseStatement(ParserContext *ctx) = 0;
};
