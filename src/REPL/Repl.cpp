#include "Repl.h"

Repl::Repl()
    : showSyntaxTree(false), showBoundTree(false), braceCount(0), exit(false) {}

Repl::~Repl() {}

void Repl::run() {
  printWelcomeMessage(std::cout);
  runWithStream(std::cin, std::cout);
}

void Repl::runWithStream(std::istream &inputStream,
                         std::ostream &outputStream) {

  // std::vector<std::string> text = {"2+5"};
  // std::unique_ptr<Parser> p = std::make_unique<Parser>(text);

  // std::unique_ptr<CompilationUnitSyntax> cu =
  //     std::move(p->parseCompilationUnit());

  // Utils::prettyPrint(cu.get());
  // std::unique_ptr<BoundScopeGlobal> gs =
  //     std::move(Binder::bindGlobalScope(nullptr, cu.get()));

  // Utils::prettyPrint(gs->statement.get());

  // llvm::Value *generatedIR =
  //     _evaluator->generateEvaluateStatement(gs->statement.get());
  // // std::any result = currentEvaluator->last_value;
  // _evaluator->printIR();
  // _evaluator->executeGeneratedCode();

  while (!exit) {
    outputStream << GREEN << ">>> " << RESET;

    std::vector<std::string> text = std::vector<std::string>();
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

        outputStream << YELLOW << "... " << RESET;
        continue;
      }
      emptyLines = 0;

      text.push_back(line);

      parser = std::make_shared<Parser>(text);

      if (parser->logs.size()) {
        Utils::printErrors(parser->logs, outputStream);
        text = std::vector<std::string>();

        break;
      }
      compilationUnit = (parser->parseCompilationUnit());

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
      compileAndEvaluate(outputStream);

      text = std::vector<std::string>();
    }
  }
}

void Repl::compileAndEvaluate(std::ostream &outputStream) {

  globalScope = Binder::bindGlobalScope(nullptr, compilationUnit.get());

  if (showBoundTree) {
    Utils::prettyPrint(globalScope->statement.get());
    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>();
    llvm::Value *generatedIR =
        _evaluator->generateEvaluateStatement(globalScope->statement.get());
    _evaluator->printIR();
    _evaluator->executeGeneratedCode();

    if (globalScope->logs.size()) {
      Utils::printErrors(globalScope->logs, outputStream);
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
    compileAndEvaluate(outputStream);
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