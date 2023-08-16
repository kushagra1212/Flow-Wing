
#ifndef REPL_H
#define REPL_H
#include "../Common.h"
#include "../evaluator/Evaluator.h"
#include "../evaluator/llvm/IRGenerator.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
class Repl {
public:
  Repl();
  ~Repl();

  // Run the REPL with default input/output streams
  void run();

  // Run the REPL with custom input/output streams for testing
  void runWithStream(std::istream &inputStream, std::ostream &outputStream);
  void runForTest(std::istream &inputStream, std::ostream &outputStream);
  bool isSyntaxTreeVisible() const;
  bool isBoundTreeVisible() const;
  // Helper functions
  void printWelcomeMessage(std::ostream &outputStream);
  bool handleSpecialCommands(const std::string &line);
  int countBraces(const std::string &line, char brace);

  void
  compileAndEvaluate(std::ostream &outputStream,
                     std::unique_ptr<CompilationUnitSyntax> compilationUnit);

  void toggleExit();
  // Data members
private:
  bool showSyntaxTree, showBoundTree, exit;
  std::unique_ptr<BoundScopeGlobal> globalScope;

  int braceCount;
  std::vector<std::string> text = std::vector<std::string>();
};

#endif // REPL_H