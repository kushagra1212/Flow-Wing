#pragma once

#include "../../../../syntax/expression/BracketedExpressionSyntax/BracketedExpressionSyntax.h"
#include "../ContainerExpressionParser/ContainerExpressionParser.h"
#include "../ExpressionParser.h"
#include "../FillExpressionParser/FillExpressionParser.h"
#include "../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../PrecedenceAwareExpressionParser.h"

class BracketedExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};