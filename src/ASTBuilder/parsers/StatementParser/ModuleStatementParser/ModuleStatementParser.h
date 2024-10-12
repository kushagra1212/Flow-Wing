#pragma once

#include "../../../../syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"
#include "../../ExpressionParser/CallExpressionParser/CallExpressionParser.h"
#include "../../ExpressionParser/LiteralExpressionParserUtils/LiteralExpressionParserUtils.h"
#include "../../ExpressionParser/StringExpressionParser/StringExpressionParser.h"
#include "../../ParserUtils/VariableParserUtils.h"
#include "../ClassStatementParser/ClassStatementParser.h"
#include "../CustomTypeStatementParser/CustomTypeStatementParser.h"
#include "../FunctionDeclarationParser/FunctionDeclarationParser.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class ModuleStatementParser : public StatementParser {

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;
};