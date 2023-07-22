
#include "Common.h"
#include "compiler/Evaluator.h"
#include "parser/Parser.h"
#include "utils/Utils.h"
#include <any>
// ANSI color codes
constexpr auto RESET = "\033[0m";
constexpr auto RED = "\033[31m";
constexpr auto GREEN = "\033[32m";
constexpr auto YELLOW = "\033[33m";
constexpr auto BLUE = "\033[34m";
int countBraces(const std::string &line, const char &brace) {
  int count = 0;
  for (char c : line) {
    if (c == brace) {
      count++;
    }
  }
  return count;
}

int main() {

  SyntaxKindUtils::init_enum_to_string_map();
  std::string line;
  std::shared_ptr<Evaluator> previousEvaluator = nullptr;
  bool seeTree = false;
  std::vector<std::string> text;
  int braceCount = 0;
  while (true) {
    if (braceCount) {
      std::cout << YELLOW << "... " << RESET;
    } else {
      std::cout << GREEN << ">>> " << RESET;
    }
    std::getline(std::cin, line);
    if (line == "") {
      continue;
    }
    if (line == "`exit") {
      break;
    }
    if (line == "`cls") {
      system("clear");
      continue;
    }
    if (line == "`tree") {
      seeTree = true;
      continue;
    }
    text.push_back(line);

    braceCount = countBraces(line, '{') - countBraces(line, '}') + braceCount;

    if (braceCount) {
      continue;
    }
    Parser *parser = new Parser(text);

    std::shared_ptr<CompilationUnitSyntax> compilationUnit =
        (parser->parseCompilationUnit());

    std::shared_ptr<Evaluator> currentEvaluator =
        previousEvaluator == nullptr
            ? std::make_shared<Evaluator>(previousEvaluator, compilationUnit)
            : previousEvaluator->continueWith(compilationUnit);
    BoundScopeGlobal *global_scope = currentEvaluator->getRoot();

    compilationUnit->logs.insert(compilationUnit->logs.end(),
                                 global_scope->logs.begin(),
                                 global_scope->logs.end());

    text = std::vector<std::string>();

    if (seeTree) {
      Utils::prettyPrint(compilationUnit->getStatement());
    }
    if (compilationUnit->logs.size()) {
      for (int i = 0; i < compilationUnit->logs.size(); i++) {
        std::cout << RED << compilationUnit->logs[i] << RESET << std::endl;
      }

    } else {
      try {

        currentEvaluator->evaluateStatement(global_scope->statement);

        std::any result = currentEvaluator->last_value;

        if (currentEvaluator->getRoot()->logs.size()) {
          for (int i = 0; i < currentEvaluator->getRoot()->logs.size(); i++) {
            std::cout << RED << currentEvaluator->getRoot()->logs[i] << RESET
                      << std::endl;
          }

        } else {
          if (result.type() == typeid(int)) {
            int intValue = std::any_cast<int>(result);
            std::cout << intValue << std::endl;
          } else if (result.type() == typeid(bool)) {
            bool boolValue = std::any_cast<bool>(result);
            std::cout << (boolValue ? "true" : "false") << std::endl;
          } else if (result.type() == typeid(std::string)) {
            std::string stringValue = std::any_cast<std::string>(result);
            std::cout << stringValue << std::endl;
          } else if (result.type() == typeid(double)) {
            double doubleValue = std::any_cast<double>(result);
            std::cout << doubleValue << std::endl;
          } else if (result.type() == typeid(std::nullptr_t)) {
            std::cout << "hi";
          } else {
            std::runtime_error("Unexpected result type");
          }
        }
      } catch (std::exception &e) {
        std::cout << RED << e.what() << RESET << std::endl;
      }

      previousEvaluator = (currentEvaluator);
    }
  }

  return 0;
}
