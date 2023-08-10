#include "Compiler.h"
#include "../parser/Parser.h"
#include "../syntax/CompilationUnitSyntax.h"
#include "../utils/Utils.h"
#include <fstream>
#include <iostream>

Compiler::Compiler() = default;

Compiler::~Compiler() = default;

int Compiler::compile(const std::vector<std::string> &text) {

  try {
    Parser *parser = new Parser(text);
    if (parser->logs.size()) {
      Utils::printErrors(parser->logs, std::cerr);
      return 0;
    }
    CompilationUnitSyntax *compilationUnit = (parser->parseCompilationUnit());
    if (parser->logs.size()) {
      Utils::printErrors(parser->logs, std::cerr);
      return 0;
    }

    Evaluator *currentEvaluator = new Evaluator(nullptr, compilationUnit);

    BoundScopeGlobal *globalScope = currentEvaluator->getRoot();
    if (globalScope->logs.size()) {
      Utils::printErrors(globalScope->logs, std::cerr);
      return 0;
    }
    currentEvaluator->evaluateStatement(globalScope->statement);
    std::any result = currentEvaluator->last_value;

    if (globalScope->logs.size()) {
      Utils::printErrors(globalScope->logs, std::cerr);
      return 0;
    }

    return 1;

  } catch (const std::exception &e) {
    std::vector<std::string> logs = std::vector<std::string>();
    logs.push_back(e.what());
    Utils::printErrors(logs, std::cerr);
    return 0;
  }
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
    return 0;
  }

  // Open the file using the provided file path
  std::ifstream file(argv[1]);

  // Check if the file was opened successfully
  if (!file.is_open()) {  
    std::cerr << "Could not open the file." << std::endl;
    return 0;
  }

  // Read and display the content line by line
  std::string line;
  std::vector<std::string> text = std::vector<std::string>();
  while (std::getline(file, line)) {
    text.push_back(line);
  }
  // Close the file
  file.close();
  Compiler *compiler = new Compiler();
  return compiler->compile(text);

  return 0;
}
