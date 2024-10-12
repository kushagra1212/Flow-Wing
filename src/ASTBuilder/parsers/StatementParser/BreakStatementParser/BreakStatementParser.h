#pragma once

#include "../../../../syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class BreakStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};