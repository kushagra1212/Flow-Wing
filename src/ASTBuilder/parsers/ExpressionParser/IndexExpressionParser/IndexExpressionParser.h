#pragma once

#include "../../../../syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "../ExpressionParser.h"
#include "../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../PrecedenceAwareExpressionParser.h"

class IndexExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};