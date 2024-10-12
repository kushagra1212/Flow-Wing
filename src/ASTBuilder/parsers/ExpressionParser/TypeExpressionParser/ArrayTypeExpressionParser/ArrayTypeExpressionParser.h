#pragma once

#include "../../../../../syntax/expression/TypeExpressionSyntax/ArrayTypeExpressionSyntax/ArrayTypeExpressionSyntax.h"
#include "../../../../../syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include "../../ExpressionParser.h"
#include "../../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../../PrecedenceAwareExpressionParser.h"
#include "../ObjectTypeExpressionParser/ObjectTypeExpressionParser.h"
#include "../PrimitiveTypeExpressionParser/PrimitiveTypeExpressionParser.h"
class ArrayTypeExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};