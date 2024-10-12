#pragma once

#include "../../../../syntax/statements/BringStatementSyntax/BringStatementSyntax.h"

#include "../../../../utils/Macros.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class BringStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};