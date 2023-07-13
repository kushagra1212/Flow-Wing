
#include "compiler/Evaluator.h"
#include "parser/Parser.h"
#include "utils/Utils.h"
using namespace std;
using namespace SyntaxKindUtils;

// ANSI color codes
constexpr auto RESET = "\033[0m";
constexpr auto RED = "\033[31m";
constexpr auto GREEN = "\033[32m";
constexpr auto YELLOW = "\033[33m";
constexpr auto BLUE = "\033[34m";

// class Compiler {

// public:
//   static int compile(string text) {
//     Parser *parser = new Parser(text);

//     // CompilationUnitSyntax *compilationUnit =
//     parser->parseCompilationUnit();
//     // return Evaluator::evaluate(compilationUnit->getExpression());
//     return 0;
//   }
// };

int main() {

  init_enum_to_string_map();
  string line;
  bool seeTree = false;
  while (true) {
    getline(cin, line);
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
    Parser *parser = new Parser(line);
    CompilationUnitSyntax *compilationUnit =
        (CompilationUnitSyntax *)parser->parseCompilationUnit();
    if (seeTree)
      Utils::prettyPrint(compilationUnit->getExpression());
    if (compilationUnit->logs.size()) {
      for (int i = 0; i < parser->parseCompilationUnit()->logs.size(); i++) {
        cout << RED << parser->parseCompilationUnit()->logs[i] << RESET << endl;
      }
    } else {

      try {
        cout << GREEN << Evaluator::evaluate(compilationUnit->getExpression())
             << RESET << endl;
      } catch (const char *msg) {
        cout << RED << msg << RESET << endl;
        break;
      }
    }
  }

  return 0;
}
