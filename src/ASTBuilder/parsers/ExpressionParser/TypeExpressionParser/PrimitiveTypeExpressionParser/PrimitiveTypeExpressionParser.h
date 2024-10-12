#pragma once

#include "../../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../../PrecedenceAwareExpressionParser.h"

class PrimitiveTypeExpressionParser {
public:
  std::unique_ptr<SyntaxToken<std::any>> parseExpression(ParserContext *ctx);
};