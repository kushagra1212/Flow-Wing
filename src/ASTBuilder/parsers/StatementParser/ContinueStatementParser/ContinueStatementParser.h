#pragma once

#include "../../../../syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class ContinueStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};