#include "SingleLineCommentTokenReader.h"
#include <memory>

std::unique_ptr<SyntaxToken<std::any>>
SingleLineCommentTokenReader::readToken(SourceTokenizer &lexer) {
  std::string text = "";
  const size_t &lineN = lexer.lineNumber();
  const size_t &pos = lexer.position() + 1;
  text += lexer.currentChar();
  lexer.advancePosition(); // skip /
  text += lexer.currentChar();
  lexer.advancePosition(); // skip ;

  while (!lexer.isEOLorEOF()) {
    text += lexer.currentChar();
    lexer.advancePosition();
  }

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lineN,
      SyntaxKindUtils::SyntaxKind::CommentStatement, pos, text, nullptr);
}