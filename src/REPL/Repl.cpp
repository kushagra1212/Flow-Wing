#include "Repl.h"

Repl::Repl() : showSyntaxTree(false), showBoundTree(false), exit(false) {

  _diagnosticHandler = std::make_unique<DiagnosticHandler>();
  previousText = std::vector<std::string>();
  _previousGlobalScope = nullptr;
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
    text = previousText;

    runIfNotInTest([&]() { outputStream << "\n" << GREEN << ">> " << RESET; });
    this->_diagnosticHandler->updatePreviousLineCount(previousText.size());

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
          _previousDiagnosticHandler.reset(new DiagnosticHandler());
          break;
        }

        if (_previousDiagnosticHandler->hasError(
                DiagnosticUtils::DiagnosticType::Syntactic) ||
            _previousDiagnosticHandler->hasError(
                DiagnosticUtils::DiagnosticType::Lexical)) {

          runIfNotInTest([&]() {
            outputStream << "\n" << YELLOW << "... " << RESET;
          });
        } else {
          runIfNotInTest([&]() {
            outputStream << "\n" << GREEN << ">> " << RESET;
          });
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

        text = previousText;
        break;
      }
      compilationUnit = std::move(parser->parseCompilationUnit());

      if (this->_diagnosticHandler->hasError(
              DiagnosticUtils::DiagnosticType::Syntactic)) {
        runIfNotInTest([&]() {
          outputStream << "\n" << YELLOW << "... " << RESET;
        });

        _previousDiagnosticHandler = std::move(_diagnosticHandler);

        _diagnosticHandler.reset(new DiagnosticHandler());

        continue;
      }
      break;
    }
    if (!this->isTest && text == previousText) {
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
      _diagnosticHandler.reset(new DiagnosticHandler());
    }
  }
}

void Repl::compileAndEvaluate(
    std::ostream &outputStream,
    std::unique_ptr<CompilationUnitSyntax> compilationUnit) {

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(std::move(_previousGlobalScope),
                                        compilationUnit.get(),
                                        this->_diagnosticHandler.get()));

  const bool &hasSemanticError = this->_diagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (showBoundTree && !hasSemanticError) {
    Utils::prettyPrint(globalScope->globalStatement.get());
  }

  if (hasSemanticError) {
    _diagnosticHandler->logDiagnostics(outputStream, [](const Diagnostic &d) {
      return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
    });
    _diagnosticHandler.reset(new DiagnosticHandler());
    _previousGlobalScope = std::move(globalScope->previous);
    return;
  }

  try {
    std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(
        globalScope.get(), _diagnosticHandler.get());
    interpreter->execute(globalScope->globalStatement.get());

    if (this->_diagnosticHandler->hasError(
            DiagnosticUtils::DiagnosticType::Runtime)) {
      _diagnosticHandler->logDiagnostics(outputStream, [](const Diagnostic &d) {
        return d.getType() == DiagnosticUtils::DiagnosticType::Runtime;
      });
      _previousGlobalScope = std::move(globalScope->previous);
    } else {
      _previousGlobalScope = std::move(globalScope);
    }

  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET;
  }
}

void Repl::toggleExit() { exit = !exit; }

void Repl::runTests(std::istream &inputStream, std::ostream &outputStream) {

  std::string line;

  while (std::getline(inputStream, line)) {
    this->addTextString(line);
  }

  std::unique_ptr<DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<DiagnosticHandler>();

  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(text, currentDiagnosticHandler.get());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        std::cout, [](const Diagnostic &d) {
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
        std::cout, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Syntactic;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler());

    return;
  }

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(std::move(_previousGlobalScope),
                                        compilationUnit.get(),
                                        currentDiagnosticHandler.get()));

  const bool &hasSemanticError = currentDiagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (hasSemanticError) {
    currentDiagnosticHandler->logDiagnostics(
        std::cout, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
        });

    currentDiagnosticHandler.reset(new DiagnosticHandler());

    return;
  }

  try {
    std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(
        globalScope.get(), _diagnosticHandler.get());
    interpreter->execute(globalScope->globalStatement.get());

    if (this->_diagnosticHandler->hasError(
            DiagnosticUtils::DiagnosticType::Runtime)) {
      _diagnosticHandler->logDiagnostics(outputStream, [](const Diagnostic &d) {
        return d.getType() == DiagnosticUtils::DiagnosticType::Runtime;
      });
    } else {

      _previousGlobalScope = std::move(globalScope);
    }

  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void Repl::printWelcomeMessage(std::ostream &outputStream) {
  outputStream << GREEN << "Welcome to the " << GREEN << "Flow Wing" << YELLOW
               << " REPL!" << RESET << std::endl;
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

#ifdef REPL_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif

#ifdef REPL_MODE

int main() {
  std::unique_ptr<Repl> repl = std::make_unique<Repl>();
  repl->run();
  return 0;
}

#endif
