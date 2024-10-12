#pragma once

#include "../../../../syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "../../../../syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "../../ParserUtils/VariableParserUtils.h"
#include "../MultipleVariableDeclarationParser/MultipleVariableDeclarationParser.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class VariableDeclarationParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};