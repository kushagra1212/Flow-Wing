#include "EndOfFileTokenReader.h"

std::unique_ptr<SyntaxToken<std::any>>
EndOfFileTokenReader::readToken(SourceTokenizer &lexer) {
  std::unique_ptr<SyntaxToken<std::any>> endOfFileToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::EndOfFileToken, lexer.position(), "", 0);

  return endOfFileToken;
}