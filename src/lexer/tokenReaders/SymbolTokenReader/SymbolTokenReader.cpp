#include "SymbolTokenReader.h"
#include <string>

std::unique_ptr<SyntaxToken<std::any>>
SymbolTokenReader::readToken(Lexer &lexer) {
  const size_t start = lexer.position();

  const std::string singleCharSymbol(1, lexer.currentChar());
  const std::string &twoCharSymbol = singleCharSymbol + lexer.peek(1);

  for (size_t i = 0; i < __gl_FLOW_WING_SYMBOLS_SIZE; ++i) {
    const auto &symbol = __gl_FLOW_WING_SYMBOLS[i];

    if (twoCharSymbol == symbol._tokenName) {
      lexer.advancePosition();
      lexer.advancePosition();
      return std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          symbol._tokenType, start, symbol._tokenName, nullptr);
    }
  }
  for (size_t i = 0; i < __gl_FLOW_WING_SYMBOLS_SIZE; ++i) {
    const auto &symbol = __gl_FLOW_WING_SYMBOLS[i];

    if (singleCharSymbol == symbol._tokenName) {
      lexer.advancePosition();
      return std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          symbol._tokenType, start, symbol._tokenName, nullptr);
    }
  }

  return badCharacterToken(lexer, start);
}

std::unique_ptr<SyntaxToken<std::any>>
SymbolTokenReader::badCharacterToken(Lexer &lexer, const size_t &start) {
  const size_t &len = lexer.getLine(lexer.lineNumber()).length() - start;

  const std::string &str = lexer.getLine(lexer.lineNumber()).substr(start, len);

  lexer.advancePosition();

  std::unique_ptr<SyntaxToken<std::any>> badSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start, str, nullptr);

  lexer.diagnosticHandler()->addDiagnostic(
      Diagnostic("Bad Character Input <" + str + ">",
                 DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Lexical,
                 Utils::getSourceLocation(badSyntaxToken.get())));

  return badSyntaxToken;
}