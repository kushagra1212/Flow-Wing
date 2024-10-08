#include "WhiteSpaceTokenReader.h"

std::unique_ptr<SyntaxToken<std::any>>
WhiteSpaceTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start = lexer.position();

  while (!lexer.isEOLorEOF() && isspace(lexer.currentChar())) {
    lexer.advancePosition();
  }

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::WhitespaceToken, start, "", 0);
}