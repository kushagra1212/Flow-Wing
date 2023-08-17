
#ifndef REPL_H
#define REPL_H
#include "../Common.h"
#include "../evaluator/llvm/IRGenerator.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
class Repl {
public:
  Repl();
  Repl(const bool &isTest);
  ~Repl();

  // Run the REPL with default input/output streams
  void run();

  // Run the REPL with custom input/output streams for testing
  void runWithStream(std::istream &inputStream, std::ostream &outputStream);
  std::string runForTest(std::istream &inputStream, std::ostream &outputStream);
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
  // Data members

  void addTextString(std::string textString);

private:
  bool showSyntaxTree, showBoundTree, exit;
  std::vector<std::string> previous_lines;
  std::vector<std::string> text = std::vector<std::string>();

  // For testing
  bool isTest;
};

#endif // REPL_H