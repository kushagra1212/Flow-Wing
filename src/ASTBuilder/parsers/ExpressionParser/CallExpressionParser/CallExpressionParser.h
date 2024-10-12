#pragma once

#include "../../../../syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "../ExpressionParser.h"
#include "../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../PrecedenceAwareExpressionParser.h"

class CallExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};