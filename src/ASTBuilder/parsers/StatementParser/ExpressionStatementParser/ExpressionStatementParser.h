#pragma once

#include "../../../../syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class ExpressionStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};