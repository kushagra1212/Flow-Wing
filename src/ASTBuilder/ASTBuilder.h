#pragma once

#include "../SourceTokenizer/SourceTokenizer.h"
#include "parsers/CompilationUnitParser/CompilationUnitParser.h"
#include "parsers/ParserContext/ParserContext.h"
#include <memory>

class ASTBuilder {
  std::unique_ptr<ParserContext> _parserCtx = nullptr;
  std::unique_ptr<SourceTokenizer> _lexer = nullptr;

public:
  ASTBuilder(const std::vector<std::string> &sourceCode,
             FlowWing::DiagnosticHandler *diagnosticHandler,
             const std::unordered_map<std::string, int8_t> &dependencyPathsMap =
                 std::unordered_map<std::string, int8_t>());

  ~ASTBuilder();

  //? getters
  const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &getTokenListRef();
  const std::string &getFormattedSourceCode();

  std::unique_ptr<CompilationUnitSyntax> createCompilationUnit();
};
