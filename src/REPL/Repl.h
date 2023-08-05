
#ifndef REPL_H
#define REPL_H
#include "../Common.h"
#include "../compiler/Evaluator.h"
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

  void compileAndEvaluate(CompilationUnitSyntax *compilationUnit,
                          std::ostream &outputStream);

  void printErrors(const std::vector<std::string> &errors,
                   std::ostream &outputStream, bool isWarning);
  // Data members
private:
  Evaluator *previousEvaluator;
  bool showSyntaxTree, showBoundTree, exit;
  int braceCount;
  std::vector<std::string> text = std::vector<std::string>();
};

#endif // REPL_H