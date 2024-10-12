#pragma once

#include "../../../../syntax/statements/SwitchStatementSyntax/SwitchStatementSyntax.h"
#include "../CaseStatementParser/CaseStatementParser.h"
#include "../ClassStatementParser/ClassStatementParser.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class SwitchStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};