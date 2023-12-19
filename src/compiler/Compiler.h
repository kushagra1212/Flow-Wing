#ifndef __FLOW__WING__COMPILER__H__
#define __FLOW__WING__COMPILER__H__

#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

class Compiler {

public:
  Compiler(std::string filePath = "");
  ~Compiler();
  void compile(std::vector<std::string> &text, std::ostream &outputStream);
  void runTests(std::istream &inputStream, std::ostream &outputStream);

  virtual void execute() = 0;

  std::string _filePath;
  std::unique_ptr<LLFileSaveStrategy> llFileSaveStrategy;
  std::vector<std::string> text = std::vector<std::string>();
  std::string executable_directory_string;
};

#endif // __FLOW__WING__COMPILER__H__