#pragma once

#include "../ExpressionParser.h"
#include "../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../PrecedenceAwareExpressionParser.h"

class DefaultPrimaryExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};