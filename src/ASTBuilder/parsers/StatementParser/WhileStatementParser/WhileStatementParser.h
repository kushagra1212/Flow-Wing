#pragma once

#include "../../../../syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class WhileStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};