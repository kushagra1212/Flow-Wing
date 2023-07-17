
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
    CompilationUnitSyntax *compilationUnit =
        (CompilationUnitSyntax *)parser->parseCompilationUnit();
    Binder *binder = new Binder();

    compilationUnit->logs.insert(compilationUnit->logs.end(),
                                 binder->logs.begin(), binder->logs.end());

    if (seeTree)
      Utils::prettyPrint(compilationUnit->getExpression());
    if (compilationUnit->logs.size()) {
      for (int i = 0; i < compilationUnit->logs.size(); i++) {
        std::cout << RED << compilationUnit->logs[i] << RESET << std::endl;
      }
      text.pop_back();
    } else {
      text = std::vector<std::string>();
      try {

        Evaluator::logs = std::vector<std::string>();
        std::any result = Evaluator::evaluate<std::any>(
            binder->bindExpression(compilationUnit->getExpression()));

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

      } catch (const char *msg) {
        std::cout << RED << msg << RESET << std::endl;
        break;
      }
    }
  }

  return 0;
}
