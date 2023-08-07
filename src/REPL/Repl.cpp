#include "Repl.h"
Repl::Repl()
    : showSyntaxTree(false), showBoundTree(false), braceCount(0),
      previousEvaluator(nullptr), exit(false) {}

Repl::~Repl() {}

void Repl::run() {
  printWelcomeMessage(std::cout);
  runWithStream(std::cin, std::cout);
}

void Repl::printErrors(const std::vector<std::string> &errors,
                       std::ostream &outputStream, bool isWarning = false) {
  for (const std::string &error : errors) {
    if (isWarning)
      outputStream << YELLOW << error << RESET << "\n";
    else
      std::cout << RED << error << RESET << "\n";
  }
}

void Repl::runWithStream(std::istream &inputStream,
                         std::ostream &outputStream) {

  while (!exit) {

    outputStream << GREEN << ">>> " << RESET;

    std::vector<std::string> text = std::vector<std::string>();
    std::string line;
    int emptyLines = 0;
    while (true) {
      std::getline(inputStream, line);
      if (handleSpecialCommands(line)) {
        break;
      }

      if (line.empty()) {
        emptyLines++;
        if (emptyLines == 2)
          break;

        outputStream << YELLOW << "... " << RESET;
        continue;
      }
      emptyLines = 0;

      text.push_back(line);
      Parser *parser = new Parser(text);

      if (parser->logs.size()) {
        printErrors(parser->logs, outputStream);
        text = std::vector<std::string>();
        break;
      }
      CompilationUnitSyntax *compilationUnit = (parser->parseCompilationUnit());

      if (parser->logs.size()) {
        emptyLines++;
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
    if (parser->logs.size()) {
      printErrors(parser->logs, outputStream);
    } else if (!exit)
      compileAndEvaluate(compilationUnit, outputStream);
  }
}

void Repl::compileAndEvaluate(CompilationUnitSyntax *compilationUnit,
                              std::ostream &outputStream) {

  Evaluator *currentEvaluator =
      new Evaluator(previousEvaluator, compilationUnit);

  BoundScopeGlobal *globalScope = currentEvaluator->getRoot();

  if (showSyntaxTree) {
    Utils::prettyPrint(compilationUnit);
  }

  if (showBoundTree) {
    Utils::prettyPrint(globalScope->statement);
  }

  try {
    currentEvaluator->evaluateStatement(globalScope->statement);
    std::any result = currentEvaluator->last_value;

    if (globalScope->logs.size()) {
      printErrors(globalScope->logs, outputStream);
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
      previousEvaluator = currentEvaluator;
    }

  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void Repl::toggleExit() { exit = !exit; }

void Repl::runForTest(std::istream &inputStream, std::ostream &outputStream) {

  std::vector<std::string> text = std::vector<std::string>();
  std::string line;
  int emptyLines = 0;
  while (true) {
    std::getline(inputStream, line);
    if (handleSpecialCommands(line)) {
      break;
    }

    if (line.empty()) {
      emptyLines++;
      if (emptyLines == 2)
        break;

      continue;
    }
    emptyLines = 0;

    text.push_back(line);
    Parser *parser = new Parser(text);

    if (parser->logs.size()) {
      printErrors(parser->logs, outputStream);
      text = std::vector<std::string>();
      break;
    }
    CompilationUnitSyntax *compilationUnit = (parser->parseCompilationUnit());

    if (parser->logs.size()) {
      emptyLines++;
      continue;
    }

    break;
  }

  if (text.size() == 0) {
    return;
  }

  Parser *parser = new Parser(text);
  CompilationUnitSyntax *compilationUnit = (parser->parseCompilationUnit());
  if (parser->logs.size()) {
    printErrors(parser->logs, outputStream);
  } else if (!exit)
    compileAndEvaluate(compilationUnit, outputStream);
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