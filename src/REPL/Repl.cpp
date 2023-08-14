#include "Repl.h"
Repl::Repl()
    : showSyntaxTree(false), showBoundTree(false), braceCount(0),
      previousEvaluator(nullptr), exit(false) {}

Repl::~Repl() {}

void Repl::run() {
  printWelcomeMessage(std::cout);
  runWithStream(std::cin, std::cout);
}

void Repl::runWithStream(std::istream &inputStream,
                         std::ostream &outputStream) {

  while (!exit) {

    outputStream << GREEN << ">>> " << RESET;

    std::vector<std::string> text = std::vector<std::string>();
    std::string line;
    int emptyLines = 0;

    std::shared_ptr<CompilationUnitSyntax> compilationUnit = nullptr;
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
        Utils::printErrors(parser->logs, outputStream);
        text = std::vector<std::string>();

        break;
      }
      compilationUnit = std::move(parser->parseCompilationUnit());

      if (parser->logs.size()) {
        emptyLines++;
        if (emptyLines == 3) {
          Utils::printErrors(parser->logs, outputStream);
        } else
          outputStream << YELLOW << "... " << RESET;
        continue;
      }

      break;
    }

    if (text.size() == 0) {
      continue;
    }

    if (!exit) {
      if (showSyntaxTree) {
        Utils::prettyPrint(compilationUnit.get());
      }
      compileAndEvaluate(compilationUnit, outputStream);
    }
  }
}

void Repl::compileAndEvaluate(
    std::shared_ptr<CompilationUnitSyntax> compilationUnit,
    std::ostream &outputStream) {

  IRGenerator *currentEvaluator =
      new IRGenerator(previousEvaluator, compilationUnit.get());

  BoundScopeGlobal *globalScope = currentEvaluator->getRoot();

  if (showBoundTree) {
    Utils::prettyPrint(globalScope->statement);
  }

  try {

    llvm::Value *generatedIR =
        currentEvaluator->generateEvaluateStatement(globalScope->statement);
    // std::any result = currentEvaluator->last_value;
    currentEvaluator->printIR();
    currentEvaluator->executeGeneratedCode();

    if (globalScope->logs.size()) {
      Utils::printErrors(globalScope->logs, outputStream);
    } else {
      // std::string outputString = Utils::convertAnyToString(result);
      // if (outputString != Utils::NULLPTR) {
      //   outputStream << outputString << "\n";
      // } else if (outputString == Utils::NULLPTR) {

      // } else {
      //   throw std::runtime_error("Unexpected result type");
      // }
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
      if (emptyLines == 200)
        break;

      continue;
    }
    emptyLines = 0;

    text.push_back(line);
    Parser *parser = new Parser(text);

    if (parser->logs.size()) {
      Utils::printErrors(parser->logs, outputStream);
      text = std::vector<std::string>();
      break;
    }
    std::shared_ptr<CompilationUnitSyntax> compilationUnit =
        (parser->parseCompilationUnit());

    if (parser->logs.size()) {
      emptyLines++;
      continue;
    }

    break;
  }

  Parser *parser = new Parser(text);
  std::shared_ptr<CompilationUnitSyntax> compilationUnit =
      (parser->parseCompilationUnit());
  if (parser->logs.size()) {
    Utils::printErrors(parser->logs, outputStream);
  } else if (!exit)
    compileAndEvaluate(compilationUnit, outputStream);
}

void Repl::printWelcomeMessage(std::ostream &outputStream) {
  outputStream << YELLOW << "Welcome to the " << GREEN << "elang" << YELLOW
               << " REPL!" << RESET << std::endl;
  outputStream << YELLOW
               << "Type `:exit` to exit, `:cls` to clear the screen.\n";
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