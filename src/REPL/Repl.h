
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

  void compileAndEvaluate(std::ostream &outputStream);

  void toggleExit();
  // Data members
private:
  std::unique_ptr<IRGenerator> _evaluator = nullptr;
  std::shared_ptr<BoundScopeGlobal> globalScope = nullptr;
  std::shared_ptr<Parser> parser = nullptr;
  std::shared_ptr<CompilationUnitSyntax> compilationUnit = nullptr;
  bool showSyntaxTree, showBoundTree, exit;
  int braceCount;
  std::vector<std::string> text = std::vector<std::string>();
};

#endif // REPL_H