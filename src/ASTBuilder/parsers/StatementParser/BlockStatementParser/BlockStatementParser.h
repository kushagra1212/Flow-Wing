#pragma once

#include "../../../../syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class BlockStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};