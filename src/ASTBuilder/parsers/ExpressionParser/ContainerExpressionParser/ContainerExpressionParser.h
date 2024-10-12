#pragma once

#include "../../../../syntax/expression/ContainerExpressionSyntax/ContainerExpressionSyntax.h"
#include "../ExpressionParser.h"
#include "../PrecedenceAwareExpressionParser.h"

class ContainerExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};