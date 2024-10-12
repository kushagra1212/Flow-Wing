#pragma once

#include "../../../../syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "../BlockStatementParser/BlockStatementParser.h"
#include "../ElseStatementParser/ElseStatementParser.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class IfStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};