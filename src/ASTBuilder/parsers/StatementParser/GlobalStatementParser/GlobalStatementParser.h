#pragma once

#include "../MemberStatementParser.h"
#include "../StatementParserFactory.h"

class GlobalStatementParser : public MemberStatementParser {

public:
  std::unique_ptr<MemberSyntax> parseStatement(ParserContext *ctx) override;
};