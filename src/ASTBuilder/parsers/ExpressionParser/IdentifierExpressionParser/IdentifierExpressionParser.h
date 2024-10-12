#pragma once

#include "../CallExpressionParser/CallExpressionParser.h"
#include "../ExpressionParser.h"
#include "../IndexExpressionParser/IndexExpressionParser.h"
#include "../ModuleIdentifierExpressionParser/ModuleIdentifierExpressionParser.h"
#include "../MultipleAssignmentExpressionParser/MultipleAssignmentExpressionParser.h"
#include "../PrecedenceAwareExpressionParser.h"
#include "../VariableExpressionParser/VariableExpressionParser.h"

class IdentifierExpressionParser : public ExpressionParser {
public:
  std::unique_ptr<ExpressionSyntax>
  parseExpression(ParserContext *ctx) override;
};