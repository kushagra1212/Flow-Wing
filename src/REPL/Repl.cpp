#include "Repl.h"

Repl::Repl()
    : showSyntaxTree(false), showBoundTree(false), braceCount(0), exit(false) {
  previous_lines = std::vector<std::string>();
}

Repl::~Repl() {}
std::mutex textMutex;

void Repl::run() {
  printWelcomeMessage(std::cout);
  runWithStream(std::cin, std::cout);
}

void Repl::runWithStream(std::istream &inputStream,
                         std::ostream &outputStream) {
  bool compiling = false;
  std::unique_ptr<Parser> parser = nullptr;
  std::unique_ptr<CompilationUnitSyntax> compilationUnit = nullptr;
  while (!exit) {
    if (compiling) {
      outputStream << "Compiling... Please wait.\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      continue;
    }
    outputStream << GREEN << ">>> " << RESET;
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

        outputStream << YELLOW << "... " << RESET;
        continue;
      }
      emptyLines = 0;

      text.push_back(line);

      for (std::string s : text) {
        outputStream << s << "\n";
      }

      parser = std::make_unique<Parser>(text);

      if (parser->logs.size()) {
        Utils::printErrors(parser->logs, outputStream);
        text = std::vector<std::string>();
        break;
      }
      compilationUnit = std::move(parser->parseCompilationUnit());

      if (parser->logs.size()) {
        outputStream << YELLOW << "... " << RESET;
        text.pop_back();
        continue;
      }
      break;
    }
    if (text.size() == previous_lines.size()) {
      continue;
    }
    if (!exit) {
      compiling = true;

      if (showSyntaxTree) {
        Utils::prettyPrint(compilationUnit.get());
      }
      compileAndEvaluate(outputStream, std::move(compilationUnit));
      compiling = false;
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

    llvm::Value *generatedIR =
        _evaluator->generateEvaluateStatement(globalScope->statement.get());
    // _evaluator->printIR();
    _evaluator->executeGeneratedCode();

    previous_lines = text;

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
    compileAndEvaluate(outputStream, nullptr);
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