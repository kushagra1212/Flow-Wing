#ifndef LEXER_H
#define LEXER_H
// Include the header for standard algorithms

#include "../Common.h"
#include "../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../syntax/SyntaxToken.h"
#include "../utils/Utils.h"
class Lexer {
public:
  std::unique_ptr<SyntaxToken<std::any>> nextToken();
  Lexer(const std::vector<std::string> &sourceCode,
        FlowWing::DiagnosticHandler *diagnosticHandler);

private:
  std::vector<std::string> _sourceCode;
  const char endOfFile = '\r';
  const char endOfLine = '\1';
  size_t lineNumber;
  size_t position;
  size_t textSize = 0;
  FlowWing::DiagnosticHandler *_diagnosticHandler;

  char getCurrent();

  void next();
  auto peek(const int64_t &offset) const -> const char;

  std::unique_ptr<SyntaxToken<std::any>> readNumber();
  std::unique_ptr<SyntaxToken<std::any>> readDecimal(const int &start);
  std::unique_ptr<SyntaxToken<std::any>> readKeyword();
  std::unique_ptr<SyntaxToken<std::any>> readWhitespace();
  std::unique_ptr<SyntaxToken<std::any>> readSymbol();
  std::unique_ptr<SyntaxToken<std::any>> readString(const int &start);
  std::unique_ptr<SyntaxToken<std::any>> readChar(const int &start);
  std::unique_ptr<SyntaxToken<std::any>> readEndOfFile();
  std::unique_ptr<SyntaxToken<std::any>> readEndOfLine();
  std::unique_ptr<SyntaxToken<std::any>> readMultiLineComment();
  std::unique_ptr<SyntaxToken<std::any>> readSingleLineComment();
  bool isEndOfLineOrFile();
};
#endif // LEXER_H