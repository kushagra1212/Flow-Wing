#pragma once

#include "../../../syntax/MemberSyntax.h"
#include "../ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "../ParserContext/ParserContext.h"

class MemberStatementParser {
public:
  virtual ~MemberStatementParser() = default;
  virtual std::unique_ptr<MemberSyntax> parseStatement(ParserContext *ctx) = 0;
};
