#include "KeywordTokenReader.h"

std::unique_ptr<SyntaxToken<std::any>>
KeywordTokenReader::readToken(Lexer &lexer) {
  const size_t &start = lexer.position();

  while (!lexer.isEOLorEOF() &&
         (isalnum(lexer.currentChar()) || lexer.currentChar() == '_')) {
    lexer.advancePosition();
  }
  const size_t &length = lexer.position() - start;
  const std::string &text =
      lexer.getLine(lexer.lineNumber()).substr(start, length);

  for (const auto &keyword : __gl_FLOW_WING_KEYWORDS) {

    if (text == keyword._tokenName) {

      if (keyword._tokenType == SyntaxKindUtils::SyntaxKind::TrueKeyword) {
        return std::make_unique<SyntaxToken<std::any>>(
            lexer.diagnosticHandler()->getAbsoluteFilePath(),
            lexer.lineNumber(), keyword._tokenType, start, text, true);
      }

      if (keyword._tokenType == SyntaxKindUtils::SyntaxKind::FalseKeyword) {
        return std::make_unique<SyntaxToken<std::any>>(
            lexer.diagnosticHandler()->getAbsoluteFilePath(),
            lexer.lineNumber(), keyword._tokenType, start, text, false);
      }

      return std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          keyword._tokenType, start, text, text);
    }
  }

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::IdentifierToken, start, text, text);
}
