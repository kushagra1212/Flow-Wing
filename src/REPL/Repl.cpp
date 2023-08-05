#include "Repl.h"
Repl::Repl()
    : showSyntaxTree(false), showBoundTree(false), braceCount(0),
      previousEvaluator(nullptr), exit(false) {}

Repl::~Repl() {}

void Repl::run() { runWithStream(std::cin, std::cout); }

void Repl::runWithStream(std::istream &inputStream,
                         std::ostream &outputStream) {
  printWelcomeMessage(outputStream);

  while (!exit) {

    outputStream << GREEN << ">>> " << RESET;

    std::vector<std::string> text = std::vector<std::string>();
    std::string line;
    int emptyLines = 0;
    while (std::getline(inputStream, line)) {
      if (line.empty()) {
        emptyLines++;
        if (emptyLines == 2) {
          break;
        }
      } else if (handleSpecialCommands(line)) {

        break;
      } else {
        emptyLines = 0;
      }

      text.push_back(line);
      Parser *parser = new Parser(text);
      CompilationUnitSyntax *compilationUnit = (parser->parseCompilationUnit());

      if (compilationUnit->logs.size()) {
        outputStream << YELLOW << "... " << RESET;
        continue;
      }
      break;
    }
    if (text.size() == 0) {
      continue;
    }

    Parser *parser = new Parser(text);

    CompilationUnitSyntax *compilationUnit = (parser->parseCompilationUnit());

    if (!exit)
      compileAndEvaluate(compilationUnit, outputStream);
  }
}

void Repl::compileAndEvaluate(CompilationUnitSyntax *compilationUnit,
                              std::ostream &outputStream) {

  Evaluator *currentEvaluator =
      new Evaluator(previousEvaluator, compilationUnit);

  BoundScopeGlobal *globalScope = currentEvaluator->getRoot();
  compilationUnit->logs.insert(compilationUnit->logs.end(),
                               globalScope->logs.begin(),
                               globalScope->logs.end());

  text = std::vector<std::string>();
  if (showSyntaxTree) {
    Utils::prettyPrint(compilationUnit);
  }

  if (showBoundTree) {
    Utils::prettyPrint(globalScope->statement);
  }
  if (compilationUnit->logs.size()) {
    for (const std::string &log : compilationUnit->logs) {
      outputStream << RED << log << RESET << "\n";
    }
    return;
  }

  try {
    currentEvaluator->evaluateStatement(globalScope->statement);
    std::any result = currentEvaluator->last_value;

    if (currentEvaluator->getRoot()->logs.size()) {
      for (const std::string &log : currentEvaluator->getRoot()->logs) {
        outputStream << RED << log << RESET << "\n";
      }
      return;
    } else {

      if (result.type() == typeid(int)) {
        int intValue = std::any_cast<int>(result);
        outputStream << intValue << "\n";
      } else if (result.type() == typeid(bool)) {
        bool boolValue = std::any_cast<bool>(result);
        outputStream << (boolValue ? "true" : "false") << "\n";
      } else if (result.type() == typeid(std::string)) {
        std::string stringValue = std::any_cast<std::string>(result);
        outputStream << stringValue << "\n";
      } else if (result.type() == typeid(double)) {
        double doubleValue = std::any_cast<double>(result);
        outputStream << doubleValue << "\n";
      } else if (result.type() == typeid(std::nullptr_t)) {
        // Handle the nullptr_t case if needed
      } else {
        throw std::runtime_error("Unexpected result type");
      }
    }
    previousEvaluator = currentEvaluator;
  } catch (const std::exception &e) {
    previousEvaluator = currentEvaluator->previous;
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void Repl::runForTest(std::istream &inputStream, std::ostream &outputStream) {

  std::string line;

  while (std::getline(inputStream, line)) {

    if (line.empty()) {
      continue;
    }

    if (line == ":exit") {
      break;
    }

    if (handleSpecialCommands(line)) {
      continue;
    }

    text.push_back(line);
    braceCount = countBraces(line, '{') - countBraces(line, '}') + braceCount;

    if (braceCount) {
      continue;
    }
    Parser *parser = new Parser(text);

    CompilationUnitSyntax *compilationUnit = parser->parseCompilationUnit();

    this->compileAndEvaluate(compilationUnit, outputStream);
  }
}

void Repl::printWelcomeMessage(std::ostream &outputStream) {
  outputStream << YELLOW << "Welcome to the " << GREEN << "elang" << YELLOW
               << " REPL!" << RESET << std::endl;
  outputStream << YELLOW
               << "Type `:exit` to exit, `:cls` to clear the screen, "
                  "and `:bt` to see the AST.\n";
}

bool Repl::handleSpecialCommands(const std::string &line) {
  if (line == ":cls") {
    system("clear");
    return true;
  } else if (line == ":st") {
    showSyntaxTree = true;
    return true;
  } else if (line == ":bt") {
    showBoundTree = true;
    return true;
  } else if (line == ":exit") {
    exit = true;
    return true;
  }
  return false;
}

int Repl::countBraces(const std::string &line, char brace) {
  int count = 0;
  for (char c : line) {
    if (c == brace) {
      count++;
    }
  }
  return count;
}

bool Repl::isSyntaxTreeVisible() const { return showSyntaxTree; }

bool Repl::isBoundTreeVisible() const { return showBoundTree; }