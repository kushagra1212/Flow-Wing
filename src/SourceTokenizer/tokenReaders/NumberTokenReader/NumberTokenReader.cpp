#include "NumberTokenReader.h"
#include "../../../diagnostics/Diagnostic/DiagnosticCodeData.h"

std::unique_ptr<SyntaxToken<std::any>>
NumberTokenReader::readToken(SourceTokenizer &lexer) {
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

  if (SyntaxKindUtils::isNumberTooLarge(text) == true) {
    std::unique_ptr<SyntaxToken<std::any>> badSyntaxToken =
        std::make_unique<SyntaxToken<std::any>>(
            lexer.diagnosticHandler()->getAbsoluteFilePath(),
            lexer.lineNumber(), SyntaxKindUtils::SyntaxKind::BadToken, start,
            text, 0);

    lexer.diagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Lexical, {text},
        Utils::getSourceLocation(badSyntaxToken.get()),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::NumberTooLargeForInt));

    return std::move(badSyntaxToken);
  }

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::NumberToken, start, text, text);
}

std::unique_ptr<SyntaxToken<std::any>>
NumberTokenReader::readDecimal(SourceTokenizer &lexer, const int &start) {
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