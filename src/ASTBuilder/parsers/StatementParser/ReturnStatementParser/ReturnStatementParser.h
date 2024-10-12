#pragma once

#include "../../../../syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class ReturnStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};