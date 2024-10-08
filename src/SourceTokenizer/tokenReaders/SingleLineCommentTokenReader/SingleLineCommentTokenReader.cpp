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
    if (lexer.isEOL()) {
      std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
          std::move(std::make_unique<EndOfFileTokenReader>()->readToken(lexer));

      lexer.diagnosticHandler()->addDiagnostic(Diagnostic(
          "Unterminated Comment Block", DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Lexical,
          Utils::getSourceLocation(newSyntaxToken.get())));

      return std::move(newSyntaxToken);
    } else {
      text += lexer.currentChar();
      lexer.advancePosition();
    }
  }
  if (lexer.isEOL()) {
    text += "\n";
    lexer.advanceLine();
  }
  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lineN,
      SyntaxKindUtils::SyntaxKind::CommentStatement, pos, text, nullptr);
}