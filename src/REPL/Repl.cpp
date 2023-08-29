#include "Repl.h"

Repl::Repl() : showSyntaxTree(false), showBoundTree(false), exit(false) {
  previous_lines = std::vector<std::string>();
  _diagnosticHandler = std::make_unique<DiagnosticHandler>();
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
std::vector<std::string>
Repl::removePrintStatements(std::vector<std::string> text) {
  std::vector<std::string> newText;
  for (std::string line : text) {

    std::string newLine = "";

    for (int i = 0; i < line.length();) {
      if (i + 4 < line.length() && line[i] == 'p' && line[i + 1] == 'r' &&
          line[i + 2] == 'i' && line[i + 3] == 'n' && line[i + 4] == 't') {
        while (i < line.length() && line[i] != ')') {
          i++;
        }
      } else {
        newLine += line[i];
      }
      i++;
    }
    newText.push_back(newLine);
  }
  return newText;
}

void Repl::runWithStream(std::istream &inputStream,
                         std::ostream &outputStream) {

  std::unique_ptr<Parser> parser = nullptr;
  std::unique_ptr<CompilationUnitSyntax> compilationUnit = nullptr;

  while (!exit) {

    runIfNotInTest([&]() { outputStream << GREEN << ">> " << RESET; });
    this->_diagnosticHandler->updatePreviousLineCount(previous_lines.size());
    text = removePrintStatements(previous_lines);
    std::string line;
    int emptyLines = 0;
    std::unique_ptr<DiagnosticHandler> _previousDiagnosticHandler =
        std::make_unique<DiagnosticHandler>();
    while (std::getline(inputStream, line)) {

      if (handleSpecialCommands(line)) {
        break;
      }

      if (line.empty()) {
        emptyLines++;
        if (emptyLines == 2) {
          _diagnosticHandler = std::move(_previousDiagnosticHandler);
          break;
        }

        if (_previousDiagnosticHandler->hasError(
                DiagnosticUtils::DiagnosticType::Syntactic) ||
            _previousDiagnosticHandler->hasError(
                DiagnosticUtils::DiagnosticType::Lexical)) {

          runIfNotInTest([&]() { outputStream << YELLOW << "... " << RESET; });
        } else {
          runIfNotInTest([&]() { outputStream << GREEN << ">> " << RESET; });
        }

        continue;
      }
      emptyLines = 0;

      text.push_back(line);

      parser = std::make_unique<Parser>(text, this->_diagnosticHandler.get());

      if (this->_diagnosticHandler->hasError(
              DiagnosticUtils::DiagnosticType::Lexical)) {
        _diagnosticHandler->logDiagnostics(
            outputStream, [](const Diagnostic &d) {
              return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
            });

        _diagnosticHandler.reset(new DiagnosticHandler());

        text = previous_lines;
        break;
      }
      compilationUnit = std::move(parser->parseCompilationUnit());

      if (this->_diagnosticHandler->hasError(
              DiagnosticUtils::DiagnosticType::Syntactic)) {
        runIfNotInTest([&]() { outputStream << YELLOW << "... " << RESET; });

        _previousDiagnosticHandler = std::move(_diagnosticHandler);

        _diagnosticHandler.reset(new DiagnosticHandler());

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
      if (this->_diagnosticHandler->hasError(
              DiagnosticUtils::DiagnosticType::Syntactic) ||
          this->_diagnosticHandler->hasError(
              DiagnosticUtils::DiagnosticType::Lexical)) {
        _diagnosticHandler->logDiagnostics(
            outputStream, [](const Diagnostic &d) {
              return d.getType() ==
                         DiagnosticUtils::DiagnosticType::Syntactic ||
                     d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
            });

        _diagnosticHandler.reset(new DiagnosticHandler());

        continue;
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
      std::move(Binder::bindGlobalScope(nullptr, compilationUnit.get(),
                                        this->_diagnosticHandler.get()));

  const bool &hasSemanticError = this->_diagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (showBoundTree && !hasSemanticError) {
    Utils::prettyPrint(globalScope->statement.get());
  }

  if (hasSemanticError) {
    _diagnosticHandler->logDiagnostics(outputStream, [](const Diagnostic &d) {
      return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
    });
    _diagnosticHandler.reset(new DiagnosticHandler());

    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator =
        std::make_unique<IRGenerator>(IRUtils::ENVIRONMENT::REPL);

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

  std::unique_ptr<DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<DiagnosticHandler>();

  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(text, currentDiagnosticHandler.get());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler());
    return;
  }

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::move(parser->parseCompilationUnit());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Syntactic)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Syntactic;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler());

    return;
  }

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(nullptr, compilationUnit.get(),
                                        currentDiagnosticHandler.get()));

  const bool &hasSemanticError = currentDiagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (hasSemanticError) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
        });

    currentDiagnosticHandler.reset(new DiagnosticHandler());

    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator =
        std::make_unique<IRGenerator>(IRUtils::ENVIRONMENT::FILE);

    _evaluator->generateEvaluateGlobalStatement(globalScope->statement.get());
    runIfNotInTest([&]() { _evaluator->printIR(); });
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

void Repl::addTextString(const std::string &textString) {

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