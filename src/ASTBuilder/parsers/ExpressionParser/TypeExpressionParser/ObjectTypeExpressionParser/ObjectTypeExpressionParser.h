#pragma once

#include "../../../../../syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include "../../ExpressionParser.h"
#include "../../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../../PrecedenceAwareExpressionParser.h"

class ObjectTypeExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};