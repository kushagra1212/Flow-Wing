#include "ASTBuilder.h"

ASTBuilder::ASTBuilder(
    const std::vector<std::string> &sourceCode,
    FlowWing::DiagnosticHandler *diagnosticHandler,
    const std::unordered_map<std::string, int8_t> &dependencyPathsMap)
    : _parserCtx(std::make_unique<ParserContext>(diagnosticHandler,
                                                 dependencyPathsMap)),
      _lexer(std::make_unique<SourceTokenizer>(sourceCode, diagnosticHandler)) {

  _parserCtx->buildTokenList(_lexer.get());
}

ASTBuilder::~ASTBuilder() { _lexer.reset(); }

std::unique_ptr<CompilationUnitSyntax> ASTBuilder::createCompilationUnit() {
  return std::make_unique<CompilationUnitParser>()->parseCompilationUnit(
      _parserCtx.get());
}

const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &
ASTBuilder::getTokenListRef() {
  return _parserCtx->getTokenListRef();
}

const std::string &ASTBuilder::getFormattedSourceCode() {
  return _parserCtx->getCodeFormatterRef()->getFormattedSourceCode();
}