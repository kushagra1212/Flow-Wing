#pragma once

#include "../../../syntax/CompilationUnitSyntax.h"
#include "../StatementParser/FunctionDeclarationParser/FunctionDeclarationParser.h"
#include "../StatementParser/GlobalStatementParser/GlobalStatementParser.h"
#include "../StatementParser/StatementParserFactory.h"

class CompilationUnitParser {

public:
  std::unique_ptr<CompilationUnitSyntax>
  parseCompilationUnit(ParserContext *ctx);

  std::unique_ptr<MemberSyntax> parseMember(ParserContext *ctx);
};