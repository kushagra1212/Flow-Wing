#pragma once

#include "../../../../../syntax/expression/TypeExpressionSyntax/FunctionTypeExpressionSyntax/FunctionTypeExpressionSyntax.h"
#include "../../ExpressionParser.h"
#include "../../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../../PrecedenceAwareExpressionParser.h"
#include "../ObjectTypeExpressionParser/ObjectTypeExpressionParser.h"
#include "../PrimitiveTypeExpressionParser/PrimitiveTypeExpressionParser.h"
#include "../TypeExpressionParser.h"

class FunctionTypeExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};