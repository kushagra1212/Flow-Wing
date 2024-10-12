#pragma once

#include "../../../../syntax/expression/AssignmentExpressionSyntax.h"
#include "../../../../syntax/expression/MultipleAssignmentExpressionSyntax/MultipleAssignmentExpressionSyntax.h"
#include "../../../../syntax/expression/VariableExpressionSyntax/VariableExpressionSyntax.h"
#include "../ExpressionParser.h"
#include "../IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "../PrecedenceAwareExpressionParser.h"
#include "../VariableExpressionParser/VariableExpressionParser.h"

class MultipleAssignmentExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};