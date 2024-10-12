#pragma once

#include "../../../../syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "../../ParserUtils/VariableParserUtils.h"
#include "../CustomTypeStatementParser/CustomTypeStatementParser.h"
#include "../FunctionDeclarationParser/FunctionDeclarationParser.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class ClassStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};