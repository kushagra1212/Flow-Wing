#pragma once

#include "../../../../syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "../../ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class CustomTypeStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};