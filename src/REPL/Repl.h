
#ifndef REPL_H
#define REPL_H
#include "../Common.h"
#include "../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../interpreter/Interpreter.h"
#include "../parser/Parser.h"

class Repl {
public:
  Repl();
  Repl(const bool &isTest);
  ~Repl();

  // Run the REPL with default input/output streams
  void run();

  void runWithStream(std::istream &inputStream, std::ostream &outputStream);
  void runTests(std::istream &inputStream, std::ostream &outputStream);
  bool isSyntaxTreeVisible() const;
  bool isBoundTreeVisible() const;
  // Helper functions
  void printWelcomeMessage(std::ostream &outputStream);
  bool handleSpecialCommands(const std::string &line);
  int countBraces(const std::string &line, char brace);

  void
  compileAndEvaluate(std::ostream &outputStream,
                     std::unique_ptr<CompilationUnitSyntax> compilationUnit);
  void runIfNotInTest(std::function<void()> f);
  void toggleExit();

  void addTextString(const std::string &textString);

private: // Data members
  bool showSyntaxTree, showBoundTree, exit;
  std::vector<std::string> text = std::vector<std::string>();

  std::unique_ptr<DiagnosticHandler> _diagnosticHandler;
  std::unique_ptr<BoundScopeGlobal> _previousGlobalScope;
  std::vector<std::string> previousText;

  // For testing
  bool isTest;
};

#endif // REPL_H