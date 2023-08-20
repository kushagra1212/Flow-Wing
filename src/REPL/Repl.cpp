#include "Repl.h"

Repl::Repl() : showSyntaxTree(false), showBoundTree(false), exit(false) {
  previous_lines = std::vector<std::string>();
}
Repl::Repl(const bool &test) {
  Repl();
  this->isTest = test;
}
Repl::~Repl() {}
std::mutex textMutex;

void Repl::run() {
  printWelcomeMessage(std::cout);
  runWithStream(std::cin, std::cout);
}

void Repl::runIfNotInTest(std::function<void()> f) {
  if (!isTest) {
    f();
  }
}

void Repl::runWithStream(std::istream &inputStream,
                         std::ostream &outputStream) {

  std::unique_ptr<Parser> parser = nullptr;
  std::unique_ptr<CompilationUnitSyntax> compilationUnit = nullptr;
  while (!exit) {

    runIfNotInTest([&]() { outputStream << GREEN << ">> " << RESET; });
    text = previous_lines;
    std::string line;
    int emptyLines = 0;
    while (std::getline(inputStream, line)) {

      if (handleSpecialCommands(line)) {
        break;
      }

      if (line.empty()) {
        emptyLines++;
        if (emptyLines == 2)
          break;

        runIfNotInTest([&]() { outputStream << YELLOW << "... " << RESET; });
        continue;
      }
      emptyLines = 0;

      text.push_back(line);

      parser = std::make_unique<Parser>(text);

      if (parser->logs.size()) {
        Utils::printErrors(parser->logs, outputStream);
        text = previous_lines;
        break;
      }
      compilationUnit = std::move(parser->parseCompilationUnit());

      if (compilationUnit->getLogs().size()) {
        runIfNotInTest([&]() { outputStream << YELLOW << "... " << RESET; });

        continue;
      }
      break;
    }
    if (!this->isTest && text == previous_lines) {
      continue;
    }
    if (!exit) {

      if (showSyntaxTree) {
        Utils::prettyPrint(compilationUnit.get());
      }
      compileAndEvaluate(outputStream, std::move(compilationUnit));
    }
    text = std::vector<std::string>();
  }
}

void Repl::compileAndEvaluate(
    std::ostream &outputStream,
    std::unique_ptr<CompilationUnitSyntax> compilationUnit) {

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(nullptr, compilationUnit.get()));

  if (globalScope->logs.size()) {
    Utils::printErrors(globalScope->logs, outputStream);
  }
  if (showBoundTree) {
    Utils::prettyPrint(globalScope->statement.get());
  }

  if (globalScope->logs.size()) {
    return;
  }
  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>();

    _evaluator->generateEvaluateGlobalStatement(globalScope->statement.get());
    runIfNotInTest([&]() { _evaluator->printIR(); });

    _evaluator->executeGeneratedCode();

    previous_lines = text;

  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void Repl::toggleExit() { exit = !exit; }

void Repl::runForTest(std::istream &inputStream, std::ostream &outputStream) {

  std::unique_ptr<Parser> parser = std::make_unique<Parser>(text);

  if (parser->logs.size()) {
    std::cout << Utils::concatErrors(parser->logs, outputStream);
  }

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::move(parser->parseCompilationUnit());

  if (compilationUnit->getLogs().size()) {
    std::cout << Utils::concatErrors(compilationUnit->getLogs(), outputStream);
  }

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(nullptr, compilationUnit.get()));

  if (globalScope->logs.size()) {
    std::cout << Utils::concatErrors(globalScope->logs, outputStream);
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>();

    _evaluator->generateEvaluateGlobalStatement(globalScope->statement.get());
    // runIfNotInTest([&]() { _evaluator->printIR(); });
    _evaluator->executeGeneratedCode();

  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void Repl::printWelcomeMessage(std::ostream &outputStream) {
  outputStream << YELLOW << "Welcome to the " << GREEN << "elang" << YELLOW
               << " REPL!" << RESET << std::endl;
  outputStream << YELLOW
               << "Type `:exit` to exit, `:cls` to clear the screen.\n";
}

void Repl::addTextString(std::string textString) {
  this->text.push_back(textString);
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