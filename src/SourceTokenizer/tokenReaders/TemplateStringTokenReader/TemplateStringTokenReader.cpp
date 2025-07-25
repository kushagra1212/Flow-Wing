#include "TemplateStringTokenReader.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/utils/LogConfig.h"

std::unique_ptr<SyntaxToken<std::any>>
TemplateStringTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start = lexer.position();
  std::string text = "", valueText = "";
  text += lexer.currentChar();
  lexer.advancePosition();

  while (!lexer.isEOF() && lexer.currentChar() != '`') {

    if (lexer.isEOL()) {
      text += "\n";
      valueText += "\n";
      lexer.advanceLine();
    } else {
      text += lexer.currentChar();
      valueText += lexer.currentChar();
      lexer.advancePosition();
    }
  }

  if (lexer.currentChar() != '`') {
    return unTerminatedTemplateStringToken(lexer, start);
  }

  text += lexer.currentChar();
  lexer.advancePosition();

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::StringToken, start, text,

      valueText);
}

std::unique_ptr<SyntaxToken<std::any>>
TemplateStringTokenReader::unTerminatedTemplateStringToken(
    SourceTokenizer &lexer, const size_t &start) {
  std::unique_ptr<SyntaxToken<std::any>> unTerminatedToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start, "", 0);

  lexer.diagnosticHandler()->addDiagnostic(
      Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Lexical, {},
                 Utils::getSourceLocation(unTerminatedToken.get()),
                 FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                     UnTerminatedTemplateStringLiteral));

  return (unTerminatedToken);
}