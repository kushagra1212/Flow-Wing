#include "MultiLineCommentTokenReader.h"
#include <memory>

std::unique_ptr<SyntaxToken<std::any>>
MultiLineCommentTokenReader::readToken(SourceTokenizer &lexer) {
  std::string text = "";
  const size_t &lineN = lexer.lineNumber();
  const size_t &pos = lexer.position() + 1;
  text += lexer.currentChar();
  lexer.advancePosition(); // skip /
  text += lexer.currentChar();
  lexer.advancePosition(); // skip #

  while (!lexer.isEOF() &&
         (lexer.currentChar() != '#' ||
          (lexer.currentChar() == '#' && lexer.peek(1) != '/'))) {
    if (lexer.isEOL()) {
      text += "\n";
      lexer.advanceLine();
    } else {
      text += lexer.currentChar();
      lexer.advancePosition();
    }
  }

  text += lexer.currentChar();
  lexer.advancePosition();
  text += lexer.currentChar();
  lexer.advancePosition();

  if (lexer.isEOL()) {
    text += "\n";
    lexer.advanceLine();
  }
  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lineN,
      SyntaxKindUtils::SyntaxKind::CommentStatement, pos, text, nullptr);
}