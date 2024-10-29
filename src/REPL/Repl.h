
#ifndef REPL_H
#define REPL_H

#include "../ASTBuilder/ASTBuilder.h"
#include "../SemanticAnalyzer/SyntaxBinder/BoundGlobalScope/BoundGlobalScope.h"
#include "../common/Common.h"
#include "../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../interpreter/Interpreter.h"

#ifdef _WIN32
#include <Windows.h>
#endif
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
  bool showSyntaxTree = false, showBoundTree = false, exit = false;
  std::vector<std::string> text = std::vector<std::string>();

  std::unique_ptr<FlowWing::DiagnosticHandler> _diagnosticHandler = nullptr;
  std::unique_ptr<BoundGlobalScope> _previousGlobalScope = nullptr;
  std::vector<std::string> previousText;

  // For testing
  bool isTest = false;
};

#endif // REPL_H