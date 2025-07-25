#include "StringTokenReader.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"

std::unique_ptr<SyntaxToken<std::any>>
StringTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start = lexer.position();
  lexer.advancePosition();
  std::string text = "", valueText = "";
  while (!lexer.isEOLorEOF() && lexer.currentChar() != '"') {
    if (lexer.currentChar() == '\0') {
      return unTerminatedStringToken(lexer, start);
    }

    if (lexer.currentChar() == '\\') {
      text += lexer.currentChar();
      lexer.advancePosition();
      text += lexer.currentChar();
      switch (lexer.currentChar()) {
      case '"':
        valueText += '"';
        break;
      case '\\':
        valueText += '\\';
        break;
      case 'n':
        valueText += '\n';
        break;
      case 'r':
        valueText += '\r';
        break;
      case 't':
        valueText += '\t';
        break;
      default: {
        return badEscapeSequenceToken(lexer, start);
      }
      }
    } else {
      text += lexer.currentChar();
      valueText += lexer.currentChar();
    }
    lexer.advancePosition();
  }

  if (lexer.currentChar() != '"') {
    return unTerminatedStringToken(lexer, start);
  }

  lexer.advancePosition();

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::StringToken, start, '"' + text + '"',
      valueText);
}

std::unique_ptr<SyntaxToken<std::any>>
StringTokenReader::unTerminatedStringToken(SourceTokenizer &lexer,
                                           const size_t &start) {
  std::unique_ptr<SyntaxToken<std::any>> unterminatedSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start,
          lexer.getLine(lexer.lineNumber())
              .substr(start, lexer.position() - start),
          0);

  lexer.diagnosticHandler()->addDiagnostic(Diagnostic(
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Lexical, {},
      Utils::getSourceLocation(unterminatedSyntaxToken.get()),
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnTerminatedStringLiteral));

  return (unterminatedSyntaxToken);
}

std::unique_ptr<SyntaxToken<std::any>>
StringTokenReader::badEscapeSequenceToken(SourceTokenizer &lexer,
                                          const size_t &start) {
  std::unique_ptr<SyntaxToken<std::any>> badSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start,
          lexer.getLine(lexer.lineNumber())
              .substr(start, lexer.position() - start),
          0);

  lexer.diagnosticHandler()->addDiagnostic(Diagnostic(
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Lexical,
      {lexer.getLine(lexer.lineNumber()).substr(lexer.position(), 1)},
      Utils::getSourceLocation(badSyntaxToken.get()),
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::
          BadCharacterEscapeSequenceInStringLiteral));

  return (badSyntaxToken);
}