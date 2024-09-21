#ifndef __FLOW__WING__COMPILER__H__
#define __FLOW__WING__COMPILER__H__

#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../cli/commandLineOptions/commandLineOptions.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
#include "CompilerUtils.h"

class Compiler {
public:
  Compiler(std::string filePath = "");

  void compile(std::vector<std::string> &text, std::ostream &outputStream);

  void runTests(std::istream &inputStream, std::ostream &outputStream);

  virtual void execute() = 0;

  std::string _filePath;
  std::string _outputFilePath;
  std::unique_ptr<LLFileSaveStrategy> llFileSaveStrategy;
  std::vector<std::string> text = std::vector<std::string>();
  std::string executable_directory_string;
  std::unique_ptr<FlowWing::DiagnosticHandler> _currentDiagnosticHandler;
  llvm::ExecutionEngine *executionEngine;
  std::filesystem::path _executable_path = std::filesystem::current_path();
};

#endif // __FLOW__WING__COMPILER__H__