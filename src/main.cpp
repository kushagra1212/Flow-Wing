
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

int main() {

  SyntaxKindUtils::init_enum_to_string_map();
  std::string line;
  Evaluator *previousEvaluator = nullptr;
  bool seeTree = false;
  std::vector<std::string> text;
  while (true) {
    std::cout << GREEN << ">>> " << RESET;

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
    Parser *parser = new Parser(text);
    text.pop_back();

    CompilationUnitSyntax *compilationUnit =
        (CompilationUnitSyntax *)parser->parseCompilationUnit();
    Evaluator *currentEvaluator =
        previousEvaluator == nullptr
            ? new Evaluator(previousEvaluator, compilationUnit)
            : previousEvaluator->continueWith(compilationUnit);
    BoundScopeGlobal *global_scope = Binder::bindGlobalScope(
        previousEvaluator ? previousEvaluator->getRoot() : nullptr,
        compilationUnit);

    compilationUnit->logs.insert(compilationUnit->logs.end(),
                                 global_scope->logs.begin(),
                                 global_scope->logs.end());

    if (seeTree)
      Utils::prettyPrint(compilationUnit->getExpression());
    if (compilationUnit->logs.size()) {
      for (int i = 0; i < compilationUnit->logs.size(); i++) {
        std::cout << RED << compilationUnit->logs[i] << RESET << std::endl;
      }

    } else {
      try {

        std::any result =
            currentEvaluator->evaluate<std::any>(global_scope->expression);

        if (Evaluator::logs.size()) {
          for (int i = 0; i < Evaluator::logs.size(); i++) {
            std::cout << RED << Evaluator::logs[i] << RESET << std::endl;
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

          } else {
            throw "Unexpected result type";
          }
        }
        previousEvaluator = currentEvaluator;

      } catch (const char *msg) {
        std::cout << RED << msg << RESET << std::endl;
      }
    }
  }

  return 0;
}
