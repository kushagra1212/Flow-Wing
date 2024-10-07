#include "NumberTokenReader.h"

std::unique_ptr<SyntaxToken<std::any>>
NumberTokenReader::readToken(Lexer &lexer) {
  int start = lexer.position();

  while (!lexer.isEOLorEOF() && isdigit(lexer.currentChar())) {
    lexer.advancePosition();
  }

  //  double check

  if (lexer.currentChar() == '.') {
    return readDecimal(lexer, start);
  }

  const size_t &length = lexer.position() - start;
  const std::string &text =
      lexer.getLine(lexer.lineNumber()).substr(start, length);

  if (SyntaxKindUtils::isInt64(text) == false) {
    std::unique_ptr<SyntaxToken<std::any>> badSyntaxToken =
        std::make_unique<SyntaxToken<std::any>>(
            lexer.diagnosticHandler()->getAbsoluteFilePath(),
            lexer.lineNumber(), SyntaxKindUtils::SyntaxKind::BadToken, start,
            text, 0);

    lexer.diagnosticHandler()->addDiagnostic(
        Diagnostic("Bad Number Input Not Int64: " + text,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Lexical,
                   Utils::getSourceLocation(badSyntaxToken.get())));

    return std::move(badSyntaxToken);
  }

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::NumberToken, start, text, text);
}

std::unique_ptr<SyntaxToken<std::any>>
NumberTokenReader::readDecimal(Lexer &lexer, const int &start) {
  lexer.advancePosition();
  while (!lexer.isEOLorEOF() && isdigit(lexer.currentChar())) {
    lexer.advancePosition();
  }

  if (lexer.currentChar() == 'd') {
    lexer.advancePosition();
  }

  const int &length = lexer.position() - start;
  const std::string &text =
      lexer.getLine(lexer.lineNumber()).substr(start, length);

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::NumberToken, start, text, text);
}