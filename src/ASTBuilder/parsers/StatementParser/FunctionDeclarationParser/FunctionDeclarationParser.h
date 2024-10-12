#pragma once

#include "../../../../syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../../ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "../../ParserUtils/VariableParserUtils.h"
#include "../MemberStatementParser.h"
#include "../StatementParserFactory.h"

class FunctionDeclarationParser : public MemberStatementParser {

public:
  std::unique_ptr<MemberSyntax> parseStatement(ParserContext *ctx) override;
};