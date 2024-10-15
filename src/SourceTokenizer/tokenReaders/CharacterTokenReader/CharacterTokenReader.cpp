#include "CharacterTokenReader.h"

std::unique_ptr<SyntaxToken<std::any>>
CharacterTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start = lexer.position();
  lexer.advancePosition();
  std::string text = "", valueText = "";
  while (!lexer.isEOLorEOF() && lexer.currentChar() != '\'') {
    if (lexer.currentChar() == '\0') {
      return unTerminatedCharacterToken(lexer, start);
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
  if (lexer.currentChar() != '\'') {
    return unTerminatedCharacterToken(lexer, start);
  }

  lexer.advancePosition();
  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::CharacterToken, start, '\'' + text + '\'',
      valueText);
}

std::unique_ptr<SyntaxToken<std::any>>
CharacterTokenReader::unTerminatedCharacterToken(SourceTokenizer &lexer,
                                                 const size_t &start) {
  std::unique_ptr<SyntaxToken<std::any>> unTerminatedSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start,
          lexer.getLine(lexer.lineNumber())
              .substr(start, lexer.position() - start),
          0);

  lexer.diagnosticHandler()->addDiagnostic(Diagnostic(
      "Unterminated Character Literal", DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Lexical,
      Utils::getSourceLocation(unTerminatedSyntaxToken.get())));

  return (unTerminatedSyntaxToken);
}

std::unique_ptr<SyntaxToken<std::any>>
CharacterTokenReader::badEscapeSequenceToken(SourceTokenizer &lexer,
                                             const size_t &start) {
  std::unique_ptr<SyntaxToken<std::any>> badSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start,
          lexer.getLine(lexer.lineNumber())
              .substr(start, lexer.position() - start),
          0);

  lexer.diagnosticHandler()->addDiagnostic(Diagnostic(
      "Bad Character Escape Sequence: \\" +
          lexer.getLine(lexer.lineNumber()).substr(lexer.position(), 1),
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Lexical,
      Utils::getSourceLocation(badSyntaxToken.get())));

  return (badSyntaxToken);
}