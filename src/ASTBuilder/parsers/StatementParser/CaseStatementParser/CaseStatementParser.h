#pragma once

#include "../../../../syntax/statements/CaseStatementSyntax/CaseStatementSyntax.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class CaseStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};