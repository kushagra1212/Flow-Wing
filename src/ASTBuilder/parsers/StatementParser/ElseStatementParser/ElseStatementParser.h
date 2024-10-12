#pragma once

#include "../../../../syntax/statements/ElseClauseSyntax/ElseClauseSyntax.h"
#include "../BlockStatementParser/BlockStatementParser.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class ElseStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};