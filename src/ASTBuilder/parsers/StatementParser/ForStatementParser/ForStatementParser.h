#pragma once

#include "../../../../syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "../ExpressionStatementParser/ExpressionStatementParser.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"
#include "../VariableDeclarationParser/VariableDeclarationParser.h"

class ForStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};