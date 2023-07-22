#include "Repl.h"
Repl::Repl() : seeTree(false), braceCount(0) {}

Repl::~Repl() {}

void Repl::run() { runWithStream(std::cin, std::cout); }

void Repl::runWithStream(std::istream &inputStream,
                         std::ostream &outputStream) {
  printWelcomeMessage(outputStream);

  SyntaxKindUtils::init_enum_to_string_map();
  std::string line;

  while (std::getline(inputStream, line)) {
    if (braceCount) {
      outputStream << YELLOW << "... " << RESET;
    } else {
      outputStream << GREEN << ">>> " << RESET;
    }
    // Common Function to run both REPL and tests
    if (line.empty()) {
      continue;
    }

    if (line == "`:exit") {
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
    compileAndEvaluate(line, outputStream);
  }
}

void Repl::compileAndEvaluate(const std::string &line,
                              std::ostream &outputStream) {

  Parser *parser = new Parser(text);
  std::shared_ptr<CompilationUnitSyntax> compilationUnit =
      parser->parseCompilationUnit();
  delete parser;

  std::shared_ptr<Evaluator> currentEvaluator =
      previousEvaluator == nullptr
          ? std::make_shared<Evaluator>(previousEvaluator, compilationUnit)
          : previousEvaluator->continueWith(compilationUnit);

  BoundScopeGlobal *globalScope = currentEvaluator->getRoot();
  compilationUnit->logs.insert(compilationUnit->logs.end(),
                               globalScope->logs.begin(),
                               globalScope->logs.end());

  text = std::vector<std::string>();
  previousEvaluator = currentEvaluator;

  if (seeTree) {
    Utils::prettyPrint(compilationUnit->getStatement());
  }

  if (compilationUnit->logs.size()) {
    for (const std::string &log : compilationUnit->logs) {
      outputStream << RED << log << RESET << "\n";
    }
  } else {
    try {
      currentEvaluator->evaluateStatement(globalScope->statement);
      std::any result = currentEvaluator->last_value;

      if (currentEvaluator->getRoot()->logs.size()) {
        for (const std::string &log : currentEvaluator->getRoot()->logs) {
          outputStream << RED << log << RESET << "\n";
        }
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
    } catch (const std::exception &e) {
      outputStream << RED << e.what() << RESET << "\n";
    }
  }
}

void Repl::runForTest(std::istream &inputStream, std::ostream &outputStream) {

  SyntaxKindUtils::init_enum_to_string_map();
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

    this->compileAndEvaluate(line, outputStream);
  }
}

void Repl::printWelcomeMessage(std::ostream &outputStream) {
  outputStream << YELLOW << "Welcome to the " << GREEN << "elang" << YELLOW
               << " REPL!" << RESET << std::endl;
  outputStream << YELLOW
               << "Type `:exit` to exit, `:cls` to clear the screen, "
                  "and `:tree` to see the AST.\n";
}

bool Repl::handleSpecialCommands(const std::string &line) {
  if (line == ":cls") {
    system("clear");
    return true;
  } else if (line == ":tree") {
    seeTree = true;
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

bool Repl::isTreeVisible() const { return seeTree; }