#pragma once

#include "../../../../syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include "../../../../syntax/expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "../ExpressionParser.h"
#include "../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../PrecedenceAwareExpressionParser.h"
#include "ArrayTypeExpressionParser/ArrayTypeExpressionParser.h"
#include "FunctionTypeExpressionParser/FunctionTypeExpressionParser.h"
#include "ObjectTypeExpressionParser/ObjectTypeExpressionParser.h"
#include "PrimitiveTypeExpressionParser/PrimitiveTypeExpressionParser.h"

class TypeExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};