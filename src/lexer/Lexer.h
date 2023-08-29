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
  Lexer(const std::vector<std::string> &text,
        DiagnosticHandler *diagnosticHandler);

private:
  std::vector<std::string> text;
  const char endOfFile = '\0';
  const char endOfLine = '\r';
  size_t lineNumber;
  size_t position;
  size_t textSize = 0;
  DiagnosticHandler *_diagnosticHandler;

  char getCurrent();

  void next();

  std::unique_ptr<SyntaxToken<std::any>> readNumber();
  std::unique_ptr<SyntaxToken<std::any>> readDecimal(const int &start);
  std::unique_ptr<SyntaxToken<std::any>> readKeyword();
  std::unique_ptr<SyntaxToken<std::any>> readWhitespace();
  std::unique_ptr<SyntaxToken<std::any>> readSymbol();
  std::unique_ptr<SyntaxToken<std::any>> readString(const int &start);
  std::unique_ptr<SyntaxToken<std::any>> readEndOfFile();
  std::unique_ptr<SyntaxToken<std::any>> readEndOfLine();
  std::unique_ptr<SyntaxToken<std::any>> readComment();
};
#endif // LEXER_H