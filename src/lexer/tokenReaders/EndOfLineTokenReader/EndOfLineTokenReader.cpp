#include "EndOfLineTokenReader.h"

std::unique_ptr<SyntaxToken<std::any>>
EndOfLineTokenReader::readToken(Lexer &lexer) {
  std::unique_ptr<SyntaxToken<std::any>> endOfLineToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::EndOfLineToken, lexer.position(), "", 0);

  if (lexer.currentChar() == '\n')
    lexer.advancePosition();
  else
    lexer.advanceLine();

  return (endOfLineToken);
}